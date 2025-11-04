#include "../header/Airport.h"

Airport::Airport()
{
    this->elevation = 0;
}
Airport::Airport(std::string icaoCode_, const unsigned short int& elevation_, std::string airportName_, std::string iataCode_,
                 std::vector<Runway> airportRunways_, const Weather& airportWeather_):
                    icaoCode{std::move(icaoCode_)}, elevation{elevation_},
                    airportName{std::move(airportName_)},
                    iataCode{std::move(iataCode_)},
                    airportRunways{std::move(airportRunways_)},
                    airportWeather{airportWeather_}{}
Airport::Airport(const Airport& other) = default;
Airport& Airport::operator=(const Airport& other)
{
    if (this != &other)
    {
        icaoCode = other.icaoCode;
        elevation = other.elevation;
        airportName = other.airportName;
        iataCode = other.iataCode;
        airportRunways = other.airportRunways;
        airportWeather = other.airportWeather;
    }
    return *this;
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

double Airport::getLongestRunway() const{
    double longestRw = 0;
    unsigned int index = 0;
    unsigned int rwPos = 0;
    for (const auto& rw : airportRunways)
    {
        if (longestRw < rw.getLength())
        {
            longestRw = rw.getLength();
            rwPos = index;
        }
        index++;
    }
    return rwPos;
}
Runway Airport::getRunway(const unsigned int& index) const{return this->airportRunways[index];}
const Runway& Airport::getRunway(const std::string& runwayID) const
{
    for (const auto& rw : airportRunways)
        if (rw.getRunwayID() == runwayID)
            return rw;

    throw std::runtime_error("Runway not found");
}
unsigned short int Airport::getElevation() const{return this->elevation;}
std::string Airport::getIcao() const{return this->icaoCode;}
std::vector<Runway> Airport::getAirportRunways() const{return this->airportRunways;}



