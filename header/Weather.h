#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <string>

class Weather
{
private:
    std::string weatherReportStart;
    std::string weatherReportEnd;
    std::string weatherMetar;
public:
    Weather(std::string weatherReportStart_, std::string weatherReportEnd_, std::string weatherMetar_);
    Weather(const Weather& other);
    ~Weather();
    Weather& operator=(const Weather& other);
    friend std::ostream& operator<<(std::ostream& os, const Weather& wh);
};

#endif //WEATHER_H
