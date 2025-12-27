
#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Waypoint
{
private:
    std::string waypointCode;
    double longitude, latitude;
    int maxAltitude;
    int minAltitude;
    double distanceToPrevious = 0;
    bool weatherAffected;
public:
    Waypoint() = default;
    explicit Waypoint(std::string waypointCode_, const double& longitude_, const double& latitude_,
                        const int& maxAltitude_, const int& minAltitude_, const bool& weatherAffected_);
    ~Waypoint();
    void setDistanceToPrevious(const Waypoint& other);
    [[nodiscard]] double getDistanceToPrevious() const;
    [[nodiscard]] int getMinAltitude() const;
    [[nodiscard]] std::string getWaypointCode() const;
    [[nodiscard]] static bool validWaypoint(const std::vector<Waypoint>& waypointsList, const std::string& waypointName,
                                            Waypoint& selectedWaypoint);
    [[nodiscard]] static bool compareWaypointCodes(const Waypoint& wp1, const Waypoint& wp2);
    friend std::ostream& operator<<(std::ostream& os, const Waypoint& wp);
};
#endif //WAYPOINT_H
