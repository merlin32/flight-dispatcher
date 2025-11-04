#ifndef METAR_H
#define METAR_H

#include <string>
#include <iostream>

class Metar
{
private:
    std::string airportIcao;
    std::string dateAndTime;
    std::string windInfo;
    std::string visibility;
    std::string specialConditions;
    std::string cloudsInfo;
    unsigned short int temperature;
    unsigned short int dewpoint;
    unsigned short int qnh;
    std::string additionalChanges;
public:
    Metar();
    explicit Metar(std::string airportIcao_,
              std::string dateAndTime_,
              std::string windInfo_,
              std::string visibility_,
              std::string specialConditions_,
              std::string cloudsInfo_,
              unsigned short int temperature_,
              unsigned short int dewpoint_,
              unsigned short int qnh_,
              std::string additionalChanges_);
    ~Metar();
    [[nodiscard]] unsigned short int getTemperature() const;
    [[nodiscard]] unsigned short int getQnh() const;
    [[nodiscard]] unsigned short int getWindDirection() const;
    [[nodiscard]] unsigned short int getWindSpeed() const;
    friend std::ostream&  operator<<(std::ostream& os, const Metar& mt);
};
#endif //METAR_H
