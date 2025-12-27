#include "../header/Metar.h"
#include <cmath>

Metar::Metar()
{
    this->temperature = 0;
    this->dewpoint = 0;
    this->qnh = 0;
}
Metar::Metar(std::string airportIcao_,
              std::string dateAndTime_,
              std::string windInfo_,
              std::string visibility_,
              std::string specialConditions_,
              std::string cloudsInfo_,
              unsigned short int temperature_,
              unsigned short int dewpoint_,
              unsigned short int qnh_,
              std::string additionalChanges_):
            airportIcao{std::move(airportIcao_)},
            dateAndTime{std::move(dateAndTime_)},
            windInfo{std::move(windInfo_)},
            visibility{std::move(visibility_)},
            specialConditions{std::move(specialConditions_)},
            cloudsInfo{std::move(cloudsInfo_)},
            temperature{temperature_},
            dewpoint{dewpoint_},
            qnh{qnh_},
            additionalChanges{std::move(additionalChanges_)}{}
Metar::~Metar() = default;
double Metar::calculateQhnsRatio() const{return 1013.0 / qnh;} //1013 represents the standard air pressure}
double Metar::calculateTemperaturesRatio() const{return (temperature + 273.15) / 288.15;} //288.15 represents the standard air temperature in Kelvins
double Metar::calculateWindSpeed(const int& runwayDirection) const
{
    unsigned int windDirection = std::stoi(windInfo.substr(0, 3));
    unsigned int windSpeed     = std::stoi(windInfo.substr(3, 2));
    double pi = 3.14159265358979323846;
    double angleRad = (windDirection - (runwayDirection * 10)) * pi / 180.0;
    return windSpeed * cos(angleRad);
}

std::ostream& operator<<(std::ostream& os, const Metar& mt)
{
    os << "METAR ";
    os << mt.airportIcao << " ";
    os << mt.dateAndTime << "Z ";
    os << mt.windInfo << " ";
    os << mt.visibility << " ";
    if (mt.specialConditions != " ")
        os << mt.specialConditions << " ";
    if (mt.cloudsInfo != " ")
        os << mt.cloudsInfo << " ";
    os << mt.temperature << "/";
    os << mt.dewpoint << " ";
    os << "Q" << mt.qnh << " ";
    if (mt.additionalChanges != " ")
        os << mt.additionalChanges << "\n";
    return os;
}
