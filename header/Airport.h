#ifndef AIRPORT_H
#define AIRPORT_H

#include "Runway.h"
#include "Metar.h"
#include <vector>
#include <nlohmann/json_fwd.hpp>

class Airport
{
private:
    std::string icaoCode;
    int elevation;
    std::string airportName;
    std::string iataCode;
    std::vector<Runway> airportRunways;
    Metar airportWeather;
    static void attributeValidation(const std::string& value, const std::string& attributeName);
public:
    Airport();
    explicit Airport(std::string icaoCode_, const int& elevation_, std::string airportName_, std::string iataCode_,
                     std::vector<Runway> airportRunways_, const Metar& airportWeather_);
    ~Airport();
    friend std::ostream& operator<<(std::ostream& os, const Airport& ap);
    [[nodiscard]] const Runway& getRunway(const std::string& runwayID) const;
    [[nodiscard]] int getElevation() const;
    [[nodiscard]] Metar getMetar() const;
    [[nodiscard]] static bool findAirport(const std::vector<Airport>& airportsList, const std::string& candidate, Airport& ap);
    [[nodiscard]] static bool validRunway(const std::string& runwayCode, const Airport& ap);
    [[nodiscard]] static bool compareAirportsIcao(const Airport& ap1, const Airport& ap2);
    void displayIcaoCode() const;
    void readFromJson(const nlohmann::json& obj);
};

#endif  //AIRPORT_H