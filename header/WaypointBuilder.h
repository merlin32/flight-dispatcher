
#ifndef WAYPOINTBUILDER_H
#define WAYPOINTBUILDER_H

#include "Waypoint.h"

class WaypointBuilder
{
private:
    Waypoint wp;
public:
    WaypointBuilder() = default;
    WaypointBuilder& wpCode(const std::string& code);
    WaypointBuilder& coords(double lat, double lon);
    WaypointBuilder& altitudeLimits(int min, int max);
    WaypointBuilder& weatherAffected(bool status);
    WaypointBuilder& isAirport(bool status);
    Waypoint build();
};

#endif //WAYPOINTBUILDER_H
