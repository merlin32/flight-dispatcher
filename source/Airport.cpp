#include "../header/Airport.h"

Airport::Airport()
{
    this->elevation = 0;
}
Airport::Airport(std::string icaoCode_, const unsigned short int& elevation_, std::string airportName_, std::string iataCode_,
                 std::vector<Runway> airportRunways_, const Metar& airportWeather_):
                    icaoCode{std::move(icaoCode_)}, elevation{elevation_},
                    airportName{std::move(airportName_)},
                    iataCode{std::move(iataCode_)},
                    airportRunways{std::move(airportRunways_)},
                    airportWeather{airportWeather_}{}
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
Metar Airport::getMetar() const{return this->airportWeather;}
std::vector<Runway> Airport::getAirportRunways() const {return this->airportRunways;}
bool Airport::validAirport(const std::vector<Airport>& airportsList, const std::string& candidate, Airport& ap)
{
    //using lower_bound to find the first element not less than candidate using binary search, then searching for candidate
    //lambda function is used in order to search an airport by its ICAO code
    auto position = std::lower_bound(airportsList.begin(), airportsList.end(),
                                    candidate, [](const Airport& a, const std::string& code)
                                    {
                                        return a.getIcao() < code;
                                    });
    if (position != airportsList.end() && position->getIcao() == candidate)
    {
        ap = *position;
        return true;
    }
    std::cerr << "Icao code not found! Try again!\n";
    return false;
}
bool Airport::validRunway(const std::string& runwayCode, const Airport& ap)
{
    bool found = false;
    for (const auto& i : ap.getAirportRunways())
    {
        if (runwayCode == i.getRunwayID() && i.getRwStatus())
        {
            found = true;
            return found;
        }
    }
    std::cerr << "Invalid runway selection! Choose another runway!\n";
    return false;
}
bool Airport::compareAirportsIcao(const Airport& ap1, const Airport& ap2) {return ap1.getIcao() < ap2.getIcao();}






