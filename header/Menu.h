#ifndef MENU_H
#define MENU_H

#include <nlohmann/json.hpp>
#include <fstream>
#include "Route.h"

class Menu
{
private:
    std::vector<std::shared_ptr<Aircraft>> aircraftsList;
    std::vector<Airport> airportsList;
    std::vector<Waypoint> waypointsList;

    void populateAircrafts(std::ifstream aircraftsJson);
    void populateAirports(std::ifstream airportsJson);
    void populateWaypoints(std::ifstream waypointsJson);
public:
    void initLocalData();
    void flpCreation();
};

#endif //MENU_H
