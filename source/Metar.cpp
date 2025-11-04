#include "../header/Metar.h"

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
unsigned short int Metar::getTemperature() const {return this->temperature;}
unsigned short int Metar::getQnh() const {return this->qnh;}
unsigned short int Metar::getWindDirection() const
{
    std::string windDirection = this->windInfo.substr(0, 3);
    unsigned short int degrees = std::stoi(windDirection);
    return degrees;
}
unsigned short int Metar::getWindSpeed() const
{
    std::string windSpeed = this->windInfo.substr(3, 2);
    unsigned short int speed = std::stoi(windSpeed);
    return speed;
}
std::string Metar::getSpecialConditions() const {return this->windInfo;}
std::string Metar::getAirportIcao() const {return this->airportIcao;}
std::ostream& operator<<(std::ostream& os, const Metar& mt)
{
    os << "METAR ";
    os << mt.airportIcao << " ";
    os << mt.dateAndTime << "Z ";
    os << mt.windInfo << " ";
    os << mt.visibility << " ";
    os << mt.specialConditions << " ";
    os << mt.cloudsInfo << " ";
    os << mt.temperature << "/";
    os << mt.dewpoint << " ";
    os << "Q" << mt.qnh << " ";
    os << mt.additionalChanges << "\n";
    return os;
}
