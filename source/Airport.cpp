#include "../header/Airport.h"
#include "../header/JsonUtils.h"
#include "../header/Exceptions.h"
#include <algorithm>
#include <nlohmann/json.hpp>
#include <iostream>

Airport::Airport()
{
    this->elevation = 0;
}
Airport::Airport(std::string icaoCode_, const int& elevation_, std::string airportName_, std::string iataCode_,
                 std::vector<Runway> airportRunways_, const Metar& airportWeather_):
                    icaoCode{std::move(icaoCode_)}, elevation{elevation_},
                    airportName{std::move(airportName_)},
                    iataCode{std::move(iataCode_)},
                    airportRunways{std::move(airportRunways_)},
                    airportWeather{airportWeather_}
{
    attributeValidation(icaoCode, "icaoCode");
    attributeValidation(airportName, "airportName");
    attributeValidation(iataCode, "iataCode");
}
Airport::~Airport() = default;
std::ostream& operator<<(std::ostream& os, const Airport& ap)
{
    os << ap.airportName << " information\n";
    os << "===========================================\n";
    os << "IATA: " << ap.iataCode << "\n";
    os << "ICAO: " << ap.icaoCode << "\n";
    os << "Elevation: " << ap.elevation << "ft\n";
    for (const auto& rw : ap.airportRunways)
        std::cout << rw;
    std::cout << ap.airportWeather;
    return os;
}
const Runway& Airport::getRunway(const std::string& runwayID) const
{
    for (const auto& rw : airportRunways)
        if (rw.runwayCodeMatch(runwayID) == true)
            return rw;

    throw AppException("Runway not found");
}
int Airport::getElevation() const{return this->elevation;}
Metar Airport::getMetar() const{return this->airportWeather;}
bool Airport::findAirport(const std::vector<Airport>& airportsList, const std::string& candidate, Airport& ap)
{
    //using lower_bound to find the first element not less than candidate using binary search, then searching for candidate
    //lambda function is used in order to search an airport by its ICAO code
    auto position = std::lower_bound(airportsList.begin(), airportsList.end(),
                                    candidate, [](const Airport& a, const std::string& code)
                                    {
                                        return a.icaoCode < code;
                                    });
    if (position != airportsList.end() && position->icaoCode == candidate)
    {
        ap = *position;
        return true;
    }
    std::cerr << "Icao code not found! Try again!\n";
    return false;
}
bool Airport::validRunway(const std::string& runwayCode, const Airport& ap)
{
    for (const auto& i : ap.airportRunways)
    {
        if (i.runwayCodeMatch(runwayCode) == true && i.getRwStatus())
            return true;
    }
    std::cerr << "Invalid runway selection! Choose another runway!\n";
    return false;
}
bool Airport::compareAirportsIcao(const Airport& ap1, const Airport& ap2) {return ap1.icaoCode < ap2.icaoCode;}
void Airport::attributeValidation(const std::string& value, const std::string& attributeName)
{
    if (value.empty())
        throw InvalidObjectCreation("Airport", attributeName);
}
void Airport::displayIcaoCode() const{std::cout << icaoCode;}
void Airport::readFromJson(const nlohmann::json& obj)
{
    icaoCode = readAttribute<std::string>(obj, "icaoCode");
    elevation = readAttribute<int>(obj, "elevation");
    airportName = readAttribute<std::string>(obj, "airportName");
    iataCode = readAttribute<std::string>(obj, "iataCode");
    if (!obj.contains("airportRunways"))
        throw JsonFaultyRead("airportRunways");
    for (const auto& j : obj["airportRunways"])
    {
        Runway temp;
        temp.readFromJson(j);
        airportRunways.push_back(temp);
    }
    if (!obj.contains("metar"))
        throw JsonFaultyRead("metar");
    airportWeather.readFromJson(obj["metar"][0]);
}







