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
    explicit Weather(std::string weatherReportStart_, std::string weatherReportEnd_, std::string weatherMetar_);
    ~Weather();
    Weather(const Weather& other);
    Weather& operator=(const Weather& other);
    friend std::ostream& operator<<(std::ostream& os, const Weather& wh);
};

#endif //WEATHER_H
