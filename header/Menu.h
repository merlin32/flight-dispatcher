#ifndef MENU_H
#define MENU_H

#include "Route.h"
#include <unordered_map>

class Menu
{
private:
    std::vector<std::shared_ptr<Aircraft>> aircraftsList;
    std::vector<Airport> airportsList;
    std::vector<Waypoint> waypointsList;
    std::vector<Route> flightPlans;
    std::unordered_map<std::string, std::vector<std::string>> waypointsAdjacencyList;

    void populateAircrafts(std::ifstream aircraftsJson);
    void populateAirports(std::ifstream airportsJson);
    void populateWaypoints(std::ifstream waypointsJson);
    void populateAdjacencyList(std::ifstream waypointsAdjacencyJson);
    void populateRoutes(std::ifstream routesJson);
    void saveFlightPlans();
    void deleteFlightPlan();
    void flpDisplay();
    static void continuationConfirm();
    void manualWaypointSelection(const std::string& departIcao, const std::string& arrivalIcao,
                                                    std::vector<Waypoint>& routeWaypoints);
    void automaticWaypointSelection(const std::string& departIcao, const std::string& arrivalIcao,
                                                    std::vector<Waypoint>& routeWaypoints);
    [[nodiscard]] static bool readAutoFields(const std::string& displayMessage, int& field);
    [[nodiscard]] static bool readAutoFields(const std::string& displayMessage, double& field);
public:
    void initLocalData();
    void flpCreation();
    void flpSelection();
    void mainMenu(bool& sessionTerminated);
};

#endif //MENU_H
