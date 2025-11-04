#ifndef AIRPORT_H
#define AIRPORT_H

#include "Runway.h"
#include "Weather.h"
#include <vector>

class Airport
{
private:
    std::string icaoCode;
    unsigned short int elevation;
    std::string airportName;
    std::string iataCode;
    std::vector<Runway> airportRunways;
    Weather airportWeather;
public:
    Airport();
    explicit Airport(std::string icaoCode_, const unsigned short int& elevation_, std::string airportName_, std::string iataCode_,
                     std::vector<Runway> airportRunways_, const Weather& airportWeather_);
    ~Airport();
    friend std::ostream& operator<<(std::ostream& os, const Airport& ap);
    [[nodiscard]] Runway getRunway(const unsigned int& index) const;
    [[nodiscard]] const Runway& getRunway(const std::string& runwayID) const;
    [[nodiscard]] unsigned short int getElevation() const;
    [[nodiscard]] std::string getIcao() const;
    [[nodiscard]] std::vector<Runway> getAirportRunways() const;
    [[nodiscard]] Weather getWeather() const;
};

#endif  //AIRPORT_H