#ifndef AIRPORT_H
#define AIRPORT_H

#include "Runway.h"
#include "Weather.h"
#include "Waypoint.h"
#include <vector>

class Airport
{
private:
    Waypoint coordinates;
    unsigned short int elevation;
    std::string airportName;
    std::string iataCode;
    std::vector<Runway> airportRunways;
    Weather airportWeather;
public:
    explicit Airport(const Waypoint& coordinates_, const unsigned short int& elevation_, std::string airportName_, std::string iataCode_,
            std::vector<Runway> airportRunways_, const Weather& airportWeather_);
    Airport(const Airport& other);
    ~Airport();
    friend std::ostream& operator<<(std::ostream& os, const Airport& ap);
    [[nodiscard]] double getLongestRunway() const;
    [[nodiscard]] Runway getRunway(const unsigned int& index) const;

};

#endif  //AIRPORT_H