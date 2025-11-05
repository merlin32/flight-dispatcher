
#ifndef ROUTE_H
#define ROUTE_H

#include "Airport.h"
#include "Waypoint.h"
#include "FuelManagement.h"
#include "PerformanceCalculation.h"

class Route
{
private:
    //not implemented yet: alternate selection
    int cruisingAltitude;
    double routeDistance = 0;
    std::string flightNumber, callsign;
    Airport departure, arrival;
    std::string departureRunway;
    std::string arrivalRunway;
    double blockTime = 0, airTime = 0;
    double climbDuration = 0, cruiseDuration = 0, descentDuration = 0;
    std::vector<Waypoint> waypoints;
    //TOC = top of climb
    //TOD = top of descent
    double TOC = 0, TOD = 0;
    Aircraft plane;
    FuelManagement fuelPlanning;
    PerformanceCalculation perfCalc;
public:
    explicit Route(const int& cruisingAltitude_, std::string flightNumber_, std::string callsign_,
                    const Airport& departure_, const Airport& arrival_, std::string departureRunway_, std::string arrivalRunway_,
                    const std::vector<Waypoint>& waypoints_, const Aircraft& plane_,
                    const FuelManagement& fuelPlanning_, const PerformanceCalculation& perfCalc_);
    ~Route();
    friend std::ostream& operator<<(std::ostream& os, const Route& rt);
    [[nodiscard]] bool routeInit();
private:
    void setRouteDistance();
    void setClimbDuration();
    void setCruiseDuration();
    void setDescentDuration();
    void setTOD();
    void setTOC();
    void setCruiseAltitude();
    void setAirTime();
    void setBlockTime();
    [[nodiscard]] bool maxCruiseAltitudeExceeded() const;
    [[nodiscard]] bool terrainDanger() const;
    [[nodiscard]] bool flightTooShort() const;
    //Work in progress
    // [[nodiscard]] bool rwTooNarrowDepart() const;
    // [[nodiscard]] bool rwTooNarrowArrival() const;
    [[nodiscard]] bool rwTooShortDepar() const;
    [[nodiscard]] bool rwTooShortArrival() const;
    [[nodiscard]] bool aircraftRangeExceeded() const;
    [[nodiscard]] bool getCruisingAltitude() const;
};

#endif //ROUTE_H
