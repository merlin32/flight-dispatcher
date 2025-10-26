#include "../header/Waypoint.h"

Waypoint::Waypoint(std::string waypointCode_, const double& longitude_, const double& latitude_,
                   const unsigned int& maxAltitude_, const unsigned int& minAltitude_, const bool& weatherAffected_):
                        waypointCode{std::move(waypointCode_)}, longitude{longitude_}, latitude{latitude_},
                        maxAltitude{maxAltitude_}, minAltitude{minAltitude_}, weatherAffected{weatherAffected_}{}
Waypoint::Waypoint(const Waypoint& other) = default;
Waypoint::~Waypoint() = default;
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

