#ifndef AIRPORT_H
#define AIRPORT_H

#include "Runway.h"
#include "Metar.h"
#include <vector>

class Airport
{
private:
    std::string icaoCode;
    unsigned short int elevation;
    std::string airportName;
    std::string iataCode;
    std::vector<Runway> airportRunways;
    Metar airportWeather;
    static void attributeValidation(const std::string& value, const std::string& attributeName);
public:
    Airport();
    explicit Airport(std::string icaoCode_, const unsigned short int& elevation_, std::string airportName_, std::string iataCode_,
                     std::vector<Runway> airportRunways_, const Metar& airportWeather_);
    ~Airport();
    friend std::ostream& operator<<(std::ostream& os, const Airport& ap);
    [[nodiscard]] Runway getRunway(const unsigned int& index) const;
    [[nodiscard]] const Runway& getRunway(const std::string& runwayID) const;
    [[nodiscard]] unsigned short int getElevation() const;
    [[nodiscard]] std::string getIcao() const;
    [[nodiscard]] Metar getMetar() const;
    [[nodiscard]] std::vector<Runway> getAirportRunways() const;
    [[nodiscard]] static bool validAirport (const std::vector<Airport>& airportsList, const std::string& candidate, Airport& ap);
    [[nodiscard]] static bool validRunway(const std::string& runwayCode, const Airport& ap);
    [[nodiscard]] static bool compareAirportsIcao(const Airport& ap1, const Airport& ap2);
};

#endif  //AIRPORT_H