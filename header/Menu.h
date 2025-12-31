#ifndef MENU_H
#define MENU_H

#include "Route.h"

class Menu
{
private:
    std::vector<std::shared_ptr<Aircraft>> aircraftsList;
    std::vector<Airport> airportsList;
    std::vector<Waypoint> waypointsList;
    std::vector<Route> flightPlans;

    void populateAircrafts(std::ifstream aircraftsJson);
    void populateAirports(std::ifstream airportsJson);
    void populateWaypoints(std::ifstream waypointsJson);
    void continuationConfirm() const;
public:
    void initLocalData();
    void flpCreation();
    void flpSelection();
    void mainMenu();
};

#endif //MENU_H
