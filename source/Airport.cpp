#include "../header/Airport.h"

Airport::Airport(std::string airportName_, std::string icaoCode_, std::string iataCode_,
            const double& airportLongitude_, const double& airportLatitude_,
            std::vector<Runway> airportRunways_, const Weather& airportWeather_):
                    airportName{std::move(airportName_)}, icaoCode{std::move(icaoCode_)},
                    iataCode{std::move(iataCode_)}, airportLongitude{airportLongitude_},
                    airportLatitude{airportLatitude_}, airportRunways{std::move(airportRunways_)},
                    airportWeather{airportWeather_}{}
Airport::Airport(const Airport& other) = default;
Airport::~Airport() = default;
std::ostream& operator<<(std::ostream& os, const Airport& ap)
{
    os << ap.airportName << " information\n";
    os << "===========================================\n";
    os << "IATA/ICAO: " << ap.iataCode << "/" << ap.icaoCode << "\n";
    os << "Airport longitude: " << ap.airportLongitude << "\n";
    os << "Airport latitude: " << ap.airportLatitude << "\n\n";
    for (const auto& rw : ap.airportRunways)
        std::cout << rw;
    std::cout << ap.airportWeather;
    return os;
}

unsigned int Airport::getLongestRunway() const{
    int longestRw = 0;
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
Runway Airport::getRunway(const unsigned int& index) const
{
    return this->airportRunways[index];
}

