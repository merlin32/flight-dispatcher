#include "../header/Waypoint.h"
#include <cmath>

Waypoint::Waypoint(std::string waypointCode_, const double& longitude_, const double& latitude_,
                   const int& maxAltitude_, const int& minAltitude_, const bool& weatherAffected_):
                        waypointCode{std::move(waypointCode_)}, longitude{longitude_}, latitude{latitude_},
                        maxAltitude{maxAltitude_}, minAltitude{minAltitude_}, weatherAffected{weatherAffected_}{}
Waypoint::Waypoint(const Waypoint& other) = default;
Waypoint::~Waypoint() = default;
void Waypoint::setDistanceToPrevious(const Waypoint& other)
{
    //the haversine formula can be found here: https://www.movable-type.co.uk/scripts/latlong.html
    double EarthRadiusNM = 3437.7;
    double pi = 3.14159265358979323846;
    double lat1 = this->latitude * pi / 180.0;
    double lon1 = this->longitude * pi / 180.0;
    double lat2 = other.latitude * pi / 180.0;
    double lon2 = other.longitude * pi / 180.0;
    //deltas
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    //using the Haversine formula
    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dLon / 2) * std::sin(dLon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    double distance = EarthRadiusNM * c;
    this->distanceToPrevious = distance;
}
double Waypoint::getDistanceToPrevious() const{return this->distanceToPrevious;}
int Waypoint::getMinAltitude() const{return this->minAltitude;}
std::string Waypoint::getWaypointCode() const{return this->waypointCode;}
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

