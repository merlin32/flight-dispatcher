#ifndef WEATHER_H
#define WEATHER_H

#include "Metar.h"

class Weather
{
private:
    std::string weatherReportStart;
    std::string weatherReportEnd;
    Metar weatherMetar;
public:
    explicit Weather(std::string weatherReportStart_, std::string weatherReportEnd_, const Metar& weatherMetar_);
    ~Weather();
    Weather(const Weather& other);
    Weather(Weather&& other) noexcept;
    Weather& operator=(const Weather& other);
    friend std::ostream& operator<<(std::ostream& os, const Weather& wh);
};

#endif //WEATHER_H
