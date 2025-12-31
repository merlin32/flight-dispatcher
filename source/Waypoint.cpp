#include "../header/Waypoint.h"
#include "../header/Exceptions.h"
#include <cmath>
#include <algorithm>

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
void Waypoint::setDistanceToPrevious(const Waypoint& other)
{
    //the haversine formula can be found here: https://www.movable-type.co.uk/scripts/latlong.html
    double lat1 = this->latitude * PI / 180.0;
    double lon1 = this->longitude * PI / 180.0;
    double lat2 = other.latitude * PI / 180.0;
    double lon2 = other.longitude * PI / 180.0;
    //deltas
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    //using the Haversine formula
    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dLon / 2) * std::sin(dLon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    double distance = EARTH_RADIUS_NM * c;
    this->distanceToPrevious = distance;
}
double Waypoint::getDistanceToPrevious() const{return this->distanceToPrevious;}
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
bool Waypoint::waypctCodeMatch(const std::string& currentWaypctCode) const {return currentWaypctCode == waypointCode;}
void Waypoint::displayWaypointCode() const{std::cout << waypointCode;}






