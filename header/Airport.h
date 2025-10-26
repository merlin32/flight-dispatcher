#ifndef AIRPORT_H
#define AIRPORT_H

#include "Runway.h"
#include "Weather.h"
#include <vector>

class Airport
{
private:
    std::string airportName;
    std::string icaoCode;
    std::string iataCode;
    const double airportLongitude, airportLatitude;
    std::vector<Runway> airportRunways;
    Weather airportWeather;
public:
    explicit Airport(std::string airportName_, std::string icaoCode_, std::string iataCode_,
            const double& airportLongitude_, const double& airportLatitude_,
            std::vector<Runway> airportRunways_, const Weather& airportWeather_);
    Airport(const Airport& other);
    ~Airport();
    friend std::ostream& operator<<(std::ostream& os, const Airport& ap);
    [[nodiscard]] unsigned int getLongestRunway() const;
    [[nodiscard]] Runway getRunway(const unsigned int& index) const;

};

#endif  //AIRPORT_H