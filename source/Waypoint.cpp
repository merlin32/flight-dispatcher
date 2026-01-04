#include "../header/Waypoint.h"
#include "../header/Exceptions.h"
#include "../header/JsonUtils.h"
#include "../header/WaypointBuilder.h"
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <set>

Waypoint::Waypoint(std::string waypointCode_, const double& longitude_, const double& latitude_,
                   const int& maxAltitude_ = 50000, const int& minAltitude_ = 1000, const bool& weatherAffected_ = false,
                   const bool& isAirport_ = false):
                        waypointCode{std::move(waypointCode_)}, longitude{longitude_}, latitude{latitude_},
                        maxAltitude{maxAltitude_}, minAltitude{minAltitude_}, weatherAffected{weatherAffected_},
                        isAirport{isAirport_}
{
    if (waypointCode.empty()) throw InvalidObjectCreation("Waypoint", "waypointCode");
    if (longitude < -180 || longitude > 180) throw InvalidObjectCreation("Waypoint", "longitude");
    if (latitude < -90 || latitude > 90) throw InvalidObjectCreation("Waypoint", "latitude");
}
Waypoint::~Waypoint() = default;
double Waypoint::calculateDistance(const Waypoint& wp1, const Waypoint& wp2)
{
    //the haversine formula can be found here: https://www.movable-type.co.uk/scripts/latlong.html
    double lat1 = wp1.latitude * PI / 180.0;
    double lon1 = wp1.longitude * PI / 180.0;
    double lat2 = wp2.latitude * PI / 180.0;
    double lon2 = wp2.longitude * PI / 180.0;
    //deltas
    double dLat = std::abs(lat2 - lat1);
    double dLon = std::abs(lon2 - lon1);
    //using the Haversine formula
    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dLon / 2) * std::sin(dLon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    double distance = EARTH_RADIUS_NM * c;
    return distance;
}
std::ostream& operator<<(std::ostream& os, const Waypoint& wp)
{
    os << "Waypoint code: " << wp.waypointCode << '\n';
    os << "Longitude: " << wp.longitude << '\n';
    os << "Latitude: " << wp.latitude << '\n';
    os << "Max Altitude: " << wp.maxAltitude << '\n';
    os << "Min Altitude: " << wp.minAltitude << '\n';
    os << "Weather Affected: " << wp.weatherAffected << '\n';
    return os;
}
bool Waypoint::findWaypoint(const std::vector<Waypoint>& waypointsList, const std::string& waypointName,
                            Waypoint& selectedWaypoint)
{
    auto position = std::lower_bound(waypointsList.begin(), waypointsList.end(),
                                    waypointName, [](const Waypoint& w, const std::string& name)
                                    {
                                        return w.waypointCode < name;
                                    });
    if (position != waypointsList.end() && position->waypointCode == waypointName)
    {
        selectedWaypoint = *position;
        return true;
    }
    std::cerr << waypointName << " is not valid! Select another waypoint!\n";
    return false;
}
bool Waypoint::operator<(const Waypoint& other) const{return this->waypointCode < other.waypointCode;}
bool Waypoint::belowMinAlt(const int& currentAlt) const {return currentAlt < minAltitude;}
bool Waypoint::waypointIsAirport() const{return isAirport;}
void Waypoint::displayWaypointCode() const{std::cout << waypointCode;}
Waypoint::AStarNode::AStarNode(std::string wpCode_) : wpCode{std::move(wpCode_)}{}
bool Waypoint::AStarNode::AStarNodeCompare::operator()(const AStarNode* a, const AStarNode* b) const
{
    if (a->fCost != b->fCost)
        return a->fCost < b->fCost;
    if (a->hCost != b->hCost)
        return a->hCost < b->hCost;
    return a->wpCode < b->wpCode;
}
std::vector<Waypoint> Waypoint::pathFinder(const Waypoint& depart, const Waypoint& arrival,
                                const std::vector<Waypoint>& waypointsList,
                                const std::unordered_map<std::string, std::vector<std::string>>& waypointsAdjacencyList)
{
    //sources: https://www.youtube.com/watch?v=-L-WgKMFuhE&list=PLFt_AvWsXl0cq5Umv3pMC9SPnKjfp9eGW
    //         https://www.geeksforgeeks.org/dsa/a-search-algorithm/
    //         https://www.geeksforgeeks.org/cpp/set-in-cpp-stl/

    //we have one unordered map for nodes and one for the original waypoints
    std::unordered_map<std::string, AStarNode> nodeDetails;
    std::unordered_map<std::string, const Waypoint*> waypointLookup;
    //populating each map
    for (const auto& wp : waypointsList)
    {
        nodeDetails[wp.waypointCode] = AStarNode(wp.waypointCode);
        waypointLookup[wp.waypointCode] = &wp;
    }
    //creating one set for the nodes which we have to visit and one set for the nodes we have visited already
    //each set is sorted considering the fCost parameter
    //in the fCosts are equal, we compare the hCosts and as a last resort we compare the wpCode
    std::set<AStarNode*, AStarNode::AStarNodeCompare> openList;
    std::set<AStarNode*, AStarNode::AStarNodeCompare> closedList;
    //initializing the first node, which is our departure
    //gCost is 0 for the starting node --> fCost = hCost for this step
    std::string departCode = depart.waypointCode;
    nodeDetails[departCode].gCost = 0;
    nodeDetails[departCode].hCost = calculateDistance(depart, arrival);
    nodeDetails[departCode].fCost = nodeDetails[departCode].hCost;
    //adding the starting point to the openList
    openList.insert(&nodeDetails[departCode]);
    bool foundArrival = false;
    while (!openList.empty())
    {
        //declaring a pointer to the node with the lowest fCost and adding it to the closedList
        AStarNode* current = *openList.begin();
        openList.erase(current);
        closedList.insert(current);
        //destination reached
        if (current->wpCode == arrival.waypointCode)
        {
            foundArrival = true;
            break;
        }
        //checking which might be the next optimal choice
        for (const std::string& neighborCode : waypointsAdjacencyList.at(current->wpCode))
        {
            //we iterate through each node's connections given by the adjacency list
            //if the node is not present in the closedList, we calculate the fCost, gCost and hCost
            AStarNode& neighbor = nodeDetails[neighborCode];
            if (closedList.contains(&neighbor) == false)
            {
                const Waypoint* neighborWp = waypointLookup[neighborCode];
                const Waypoint* currentWp = waypointLookup[current->wpCode];
                //each node can be made inactive due to severe weather, so there is a check for weatherAffected
                if (neighborWp->weatherAffected == false)
                {
                    double gNew = current->gCost + calculateDistance(*neighborWp, *currentWp);
                    double hNew = calculateDistance(*neighborWp, arrival);
                    double fNew = gNew + hNew;
                    //if the node hasn't been visited yet or has been visited, but we found a better path, we update the costs
                    //first the node is deleted from the set, updated and reintroduced so that there won't be any error with the set
                    if (neighbor.fCost == INFINITY || fNew < neighbor.fCost) {
                        openList.erase(&neighbor);
                        neighbor.gCost = gNew;
                        neighbor.hCost = hNew;
                        neighbor.fCost = fNew;
                        neighbor.parentWaypoint = current->wpCode;
                        openList.insert(&neighbor);
                    }
                }
            }

        }
    }
    //reconstructing the path which later on is reversed so that we get the path from departure to arrival
    if (foundArrival)
    {
        std::vector<Waypoint> path;
        std::string currentCode = arrival.waypointCode;

        while (currentCode != depart.waypointCode)
        {
            path.push_back(*waypointLookup[currentCode]);
            currentCode = nodeDetails[currentCode].parentWaypoint;
        }
        path.push_back(depart);
        std::reverse(path.begin(), path.end());
        return path;
    }
    //in case there we didn't find any suitable path
    return {};
}
void Waypoint::readFromJson(const nlohmann::json& obj)
{
    *this = WaypointBuilder().wpCode(readAttribute<std::string>(obj, "waypointCode"))
                             .coords(readAttribute<double>(obj, "latitude"), readAttribute<double>(obj, "longitude"))
                             .altitudeLimits(readAttribute<int>(obj, "minAltitude"), readAttribute<int>(obj, "maxAltitude"))
                             .weatherAffected(readAttribute<bool>(obj, "weatherAffected"))
                             .isAirport(readAttribute<bool>(obj, "isAirport"))
                             .build();
}