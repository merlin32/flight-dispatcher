
#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <nlohmann/json_fwd.hpp>

class Waypoint
{
private:
    friend class WaypointBuilder;
    static constexpr double EARTH_RADIUS_NM = 3437.7;
    static constexpr double PI = 3.14159265358979323846;
    std::string waypointCode;
    double longitude = 0;
    double latitude = 0;
    int maxAltitude = 0;
    int minAltitude = 0;
    bool weatherAffected = false;
    bool isAirport = false;
    class AStarNode
    {
    private:
        friend class Waypoint;
        std::string wpCode;
        double fCost = INFINITY; //the total estimated cost of the path through this node (f = g + h).
        double gCost = INFINITY; //the actual cost/distance from the starting point to the current node.
        double hCost = INFINITY; //the heuristic or the estimated cost from the current node to the destination.
        std::string parentWaypoint;
        class AStarNodeCompare
        {
        public:
            bool operator()(const AStarNode* a, const AStarNode* b) const;
        };
        public:
            AStarNode() = default;
            explicit AStarNode(std::string wpCode_);
    };
public:
    Waypoint() = default;
    explicit Waypoint(std::string waypointCode_, const double& longitude_, const double& latitude_,
                        const int& maxAltitude_, const int& minAltitude_, const bool& weatherAffected_,
                        const bool& isAirport_);
    ~Waypoint();
    [[nodiscard]] static double calculateDistance(const Waypoint& wp1, const Waypoint& wp2);
    [[nodiscard]] static bool findWaypoint(const std::vector<Waypoint>& waypointsList, const std::string& waypointName,
                                            Waypoint& selectedWaypoint);
    bool operator<(const Waypoint& other) const;
    [[nodiscard]] bool belowMinAlt(const int& currentAlt) const;
    [[nodiscard]] bool waypointIsAirport() const;
    void displayWaypointCode() const;
    static std::vector<Waypoint> pathFinder(const Waypoint& depart, const Waypoint& arrival,
                                            const std::vector<Waypoint>& waypointsList,
                                            const std::unordered_map<std::string, std::vector<std::string>>& waypointsAdjacencyList);
    friend std::ostream& operator<<(std::ostream& os, const Waypoint& wp);
    void readFromJson(const nlohmann::json& obj);
    static void writeWpCodesToJson(nlohmann::json& obj, const std::vector<Waypoint>& waypoints);
};

#endif //WAYPOINT_H
