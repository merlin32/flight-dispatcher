#include "../header/WaypointBuilder.h"

WaypointBuilder& WaypointBuilder::wpCode(const std::string& code) {
    wp.waypointCode = code;
    return *this;
}
WaypointBuilder& WaypointBuilder::coords(double lat, double lon) {
    wp.latitude = lat;
    wp.longitude = lon;
    return *this;
}
WaypointBuilder& WaypointBuilder::altitudeLimits(int min, int max)
{
    wp.minAltitude = min;
    wp.maxAltitude = max;
    return *this;
}
WaypointBuilder& WaypointBuilder::weatherAffected(bool status)
{
    wp.weatherAffected = status;
    return *this;
}
WaypointBuilder& WaypointBuilder::isAirport(bool status)
{
    wp.isAirport = status;
    return *this;
}
Waypoint WaypointBuilder::build()
{
    return wp;
}