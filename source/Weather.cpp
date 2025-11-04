#include "../header/Weather.h"

Weather::Weather(){}
Weather::Weather(std::string weatherReportStart_, std::string weatherReportEnd_, const Metar& weatherMetar_):
                weatherReportStart{std::move(weatherReportStart_)},
                weatherReportEnd{std::move(weatherReportEnd_)},
                weatherMetar{weatherMetar_}{}
Weather::~Weather() = default;
Weather::Weather(const Weather& other) = default;
Weather::Weather(Weather&& other) noexcept = default;
Weather& Weather::operator=(const Weather& other)
{
    if (this != &other)
    {
        weatherReportStart = other.weatherReportStart;
        weatherReportEnd = other.weatherReportEnd;
        weatherMetar = Metar(other.weatherMetar);
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
Metar Weather::getMetar() const{return this->weatherMetar;}
