#include "../header/Weather.h"

Weather::Weather(std::string weatherReportStart_, std::string weatherReportEnd_, std::string weatherMetar_):
                weatherReportStart{std::move(weatherReportStart_)},
                weatherReportEnd{std::move(weatherReportEnd_)},
                weatherMetar{std::move(weatherMetar_)}{}
Weather::~Weather() = default;
Weather::Weather(const Weather& other) = default;
Weather& Weather::operator=(const Weather& other)
{
    if (this != &other)
    {
        weatherReportStart = other.weatherReportStart;
        weatherReportEnd = other.weatherReportEnd;
        weatherMetar = other.weatherMetar;
    }
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Weather& wh)
{
    os << "Weather information\n";
    os << "=====================\n";
    os << "Weather report start time: " << wh.weatherReportStart << "\n";
    os << "Weather report end time: " << wh.weatherReportEnd << "\n";
    os << "METAR: " << wh.weatherMetar << "\n\n";
    return os;
}