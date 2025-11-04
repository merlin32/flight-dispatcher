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
    Weather();
    explicit Weather(std::string weatherReportStart_, std::string weatherReportEnd_, const Metar& weatherMetar_);
    ~Weather();
    friend std::ostream& operator<<(std::ostream& os, const Weather& wh);
    [[nodiscard]] Metar getMetar() const;
};

#endif //WEATHER_H
