#include "../header/Metar.h"
#include "../header/JsonUtils.h"
#include <cmath>
#include <iostream>

#include "../header/Exceptions.h"

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
              short int temperature_,
              short int dewpoint_,
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
            additionalChanges{std::move(additionalChanges_)}
{
    stringAttributesValidation(airportIcao, "airportIcao");
    stringAttributesValidation(dateAndTime, "dateAndTime");
    stringAttributesValidation(windInfo, "windInfo");
    stringAttributesValidation(visibility, "visibility");
    stringAttributesValidation(specialConditions, "specialConditions");
    stringAttributesValidation(cloudsInfo, "cloudsInfo");
    if (qnh < LOWEST_QNH || qnh > HIGHEST_QNH) throw InvalidObjectCreation("Metar", "qnh");
    stringAttributesValidation(additionalChanges, "additionalChanges");
}
Metar::~Metar() = default;
double Metar::calculateQhnsRatio() const{return STD_QNH / qnh;}
double Metar::calculateTemperaturesRatio() const{return (temperature + DEG_TO_KEV_CONST) / STD_TEMP;}
double Metar::calculateWindSpeed(const int& runwayDirection) const
{
    unsigned int windDirection = std::stoi(windInfo.substr(0, 3));
    unsigned int windSpeed     = std::stoi(windInfo.substr(3, 2));
    double angleRad = (windDirection - (runwayDirection * 10)) * PI / 180.0;
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
void Metar::stringAttributesValidation(const std::string& value, const std::string& attributeName)
{
    if (value.empty())
        throw InvalidObjectCreation("Metar", attributeName);
}
void Metar::readFromJson(const nlohmann::json& obj)
{
    airportIcao = readAttribute<std::string>(obj, "airportIcao");
    dateAndTime = readAttribute<std::string>(obj, "dateAndTime");
    windInfo = readAttribute<std::string>(obj, "windInfo");
    visibility = readAttribute<std::string>(obj, "visibility");
    specialConditions = readAttribute<std::string>(obj, "specialConditions");
    cloudsInfo = readAttribute<std::string>(obj, "cloudsInfo");
    temperature = readAttribute<short int>(obj, "temperature");
    dewpoint = readAttribute<short int>(obj, "dewpoint");
    qnh = readAttribute<unsigned short int>(obj, "qnh");
    additionalChanges = readAttribute<std::string>(obj, "additionalChanges");
}

