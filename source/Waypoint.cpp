#include "../header/Waypoint.h"
#include "../header/Exceptions.h"
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <set>

Waypoint::Waypoint(std::string waypointCode_, const double& longitude_, const double& latitude_,
                   const int& maxAltitude_ = 50000, const int& minAltitude_ = 1000, const bool& weatherAffected_ = false):
                        waypointCode{std::move(waypointCode_)}, longitude{longitude_}, latitude{latitude_},
                        maxAltitude{maxAltitude_}, minAltitude{minAltitude_}, weatherAffected{weatherAffected_}
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
bool Waypoint::validWaypoint(const std::vector<Waypoint>& waypointsList, const std::string& waypointName,
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
bool Waypoint::compareWaypointCodes(const Waypoint& wp1, const Waypoint& wp2)
{
    return wp1.waypointCode < wp2.waypointCode;
}
bool Waypoint::belowMinAlt(const int& currentAlt) const {return currentAlt < minAltitude;}
void Waypoint::displayWaypointCode() const{std::cout << waypointCode;}
Waypoint::AStarNode::AStarNode(const std::string& wpCode_) : wpCode{std::move(wpCode_)}, fCost{INFINITY}, gCost{INFINITY}, hCost{INFINITY}{}
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
    //creating a set for nodes which haven't been visited
    std::set<AStarNode*, AStarNode::AStarNodeCompare> openList;
    std::set<AStarNode*, AStarNode::AStarNodeCompare> closedList;
    //initializing the first node, which is our departure
    std::string departCode = depart.waypointCode;
    nodeDetails[departCode].gCost = 0;
    nodeDetails[departCode].hCost = arrival.calculateDistance(depart, arrival);
    nodeDetails[departCode].fCost = nodeDetails[departCode].hCost;
    openList.insert(&nodeDetails[departCode]);
    bool foundArrival = false;

    while (!openList.empty())
    {
        AStarNode* current = *openList.begin();
        openList.erase(current);
        closedList.insert(current);

        if (current->wpCode == arrival.waypointCode)
        {
            foundArrival = true;
            break;
        }
        for (const std::string& neighborCode : waypointsAdjacencyList.at(current->wpCode)) {
            AStarNode& neighbor = nodeDetails[neighborCode];
            if (closedList.contains(&neighbor) == false)
            {
                const Waypoint* neighborWp = waypointLookup[neighborCode];
                const Waypoint* currentWp = waypointLookup[current->wpCode];

                if (neighborWp->weatherAffected == false)
                {
                    double gNew = current->gCost + currentWp->calculateDistance(*neighborWp, *currentWp);
                    double hNew = neighborWp->calculateDistance(*neighborWp, arrival);
                    double fNew = gNew + hNew;

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
    return {};
}






