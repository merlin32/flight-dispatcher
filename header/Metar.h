#ifndef METAR_H
#define METAR_H

#include <string>
#include <nlohmann/json_fwd.hpp>

class Metar
{
private:
    static constexpr double STD_QNH = 1013; //1013 represents the standard air pressure
    static constexpr double STD_TEMP = 288.15; //288.15 represents the standard air temperature in Kelvins
    static constexpr double DEG_TO_KEV_CONST = 273.15;
    static constexpr unsigned short int LOWEST_QNH = 920;
    static constexpr unsigned short int HIGHEST_QNH = 1084;
    static constexpr double PI = 3.14159265358979323846;
    std::string airportIcao;
    std::string dateAndTime;
    std::string windInfo;
    std::string visibility;
    std::string specialConditions;
    std::string cloudsInfo;
    short int temperature;
    short int dewpoint;
    unsigned short int qnh;
    std::string additionalChanges;
    static void stringAttributesValidation(const std::string& value, const std::string& attributeName);
public:
    Metar();
    explicit Metar(std::string airportIcao_,
              std::string dateAndTime_,
              std::string windInfo_,
              std::string visibility_,
              std::string specialConditions_,
              std::string cloudsInfo_,
              short int temperature_,
              short int dewpoint_,
              unsigned short int qnh_,
              std::string additionalChanges_);
    ~Metar();
    [[nodiscard]] double calculateQhnsRatio() const;
    [[nodiscard]] double calculateTemperaturesRatio() const;
    [[nodiscard]] double calculateWindSpeed(const int& runwayDirection) const;
    friend std::ostream&  operator<<(std::ostream& os, const Metar& mt);
    void readFromJson(const nlohmann::json& obj);
};
#endif //METAR_H
