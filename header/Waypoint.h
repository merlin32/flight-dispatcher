
#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <string>
#include <iostream>

class Waypoint
{
private:
    std::string waypointCode;
    double longitude, latitude;
    unsigned int maxAltitude;
    unsigned int minAltitude;
    bool weatherAffected;
public:
    explicit Waypoint(std::string waypointCode_, const double& longitude_, const double& latitude_,
                        const unsigned int& maxAltitude_, const unsigned int& minAltitude_, const bool& weatherAffected_);
    Waypoint(const Waypoint& other);
    ~Waypoint();
    friend std::ostream& operator<<(std::ostream& os, const Waypoint& wp);
};
#endif //WAYPOINT_H
