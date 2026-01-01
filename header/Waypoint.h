
#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

class Waypoint
{
private:
    static constexpr double EARTH_RADIUS_NM = 3437.7;
    static constexpr double PI = 3.14159265358979323846;
    std::string waypointCode;
    double longitude = 0;
    double latitude = 0;
    int maxAltitude = 0;
    int minAltitude = 0;
    bool weatherAffected = false;
    class AStarNode
    {
    private:
        friend class Waypoint;
        std::string wpCode;
        double fCost;
        double gCost;
        double hCost;
        std::string parentWaypoint;
        class AStarNodeCompare
        {
        public:
            bool operator()(const AStarNode* a, const AStarNode* b) const;
        };
        public:
            AStarNode() = default;
            AStarNode(const std::string& wpCode_);
    };
public:
    Waypoint() = default;
    explicit Waypoint(std::string waypointCode_, const double& longitude_, const double& latitude_,
                        const int& maxAltitude_, const int& minAltitude_, const bool& weatherAffected_);
    ~Waypoint();
    [[nodiscard]] static double calculateDistance(const Waypoint& wp1, const Waypoint& wp2);
    [[nodiscard]] static bool validWaypoint(const std::vector<Waypoint>& waypointsList, const std::string& waypointName,
                                            Waypoint& selectedWaypoint);
    [[nodiscard]] static bool compareWaypointCodes(const Waypoint& wp1, const Waypoint& wp2);
    [[nodiscard]] bool belowMinAlt(const int& currentAlt) const;
    void displayWaypointCode() const;
    static std::vector<Waypoint> pathFinder(const Waypoint& depart, const Waypoint& arrival,
                                            const std::vector<Waypoint>& waypointsList,
                                            const std::unordered_map<std::string, std::vector<std::string>>& waypointsAdjacencyList);
    friend std::ostream& operator<<(std::ostream& os, const Waypoint& wp);
};

#endif //WAYPOINT_H
