
#ifndef ROUTE_H
#define ROUTE_H

#include "Waypoint.h"
#include "PerformanceCalculation.h"

class Route
{
private:
    //not implemented yet: alternate selection
    static constexpr int MINIMUM_CRUISE_ALT = 4000;
    static constexpr int ALT_DECREMENT = 1000;
    double routeDistance = 0;
    std::string callsign;
    Airport departure, arrival;
    std::string departureRunway;
    std::string arrivalRunway;
    double blockTime = 0, airTime = 0;
    double climbDuration = 0, cruiseDuration = 0, descentDuration = 0;
    std::vector<Waypoint> waypoints;
    //TOC = top of climb
    //TOD = top of descent
    double TOC = 0, TOD = 0;
    std::shared_ptr<Aircraft> plane;
    FuelManagement fuelPlanning;
    PerformanceCalculation perfCalc;
    int cruisingAltitude;
public:
    explicit Route(std::string callsign_,
                    const Airport& departure_, const Airport& arrival_, std::string departureRunway_, std::string arrivalRunway_,
                    const std::vector<Waypoint>& waypoints_, std::shared_ptr<Aircraft> plane_,
                    const FuelManagement& fuelPlanning_, const PerformanceCalculation& perfCalc_,
                    const int& cruisingAltitude_);
    Route(const Route& other);
    Route &operator=(Route other);
    friend void swap(Route &rt1, Route &rt2) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Route& rt);
    void routeInit();
    void displayShortInfo() const;
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
    [[nodiscard]] bool terrainDanger() const;
    [[nodiscard]] bool rwTooShortDepar() const;
    [[nodiscard]] bool rwTooShortArrival() const;
};

#endif //ROUTE_H
