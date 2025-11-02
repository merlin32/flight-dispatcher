#include "../header/Route.h"

Route::Route(const int& cruisingAltitude_, const std::string& flightNumber_, const std::string& callsign_,
                    const Airport& departure_, const Airport& arrival_, const std::string& departureRunway_, const std::string& arrivalRunway_,
                    const std::vector<Waypoint>& waypoints_, const Aircraft& plane_):
                    cruisingAltitude{cruisingAltitude_}, flightNumber{flightNumber_}, callsign{callsign_},
                    departure{departure_}, arrival{arrival_}, departureRunway{departureRunway_},
                    arrivalRunway{arrivalRunway_}, waypoints{waypoints_}, plane{plane_}{}
Route::Route(const Route& other) = default;
Route::Route(Route&& other) = default;
Route::~Route() = default;
void Route::setRouteDistance()
{
    for (const auto& waypct : waypoints)
        this->routeDistance += waypct.getDistanceToPrevious();
}
void Route::setClimbDuration()
{
    this->climbDuration = (double)(this->cruisingAltitude - this->departure.getElevation()) / plane.getClimbRate();
}
void Route::setCruiseDuration()
{
    this->cruiseDuration = (this->TOD - this->TOC) / plane.getCruisingSpeed();
}
void Route::setDescentDuration()
{
    this->descentDuration = (double)(this->cruisingAltitude - arrival.getElevation()) / plane.getDescentRate();
}
void Route::setTOD()
{
    this->TOD = (climbDuration * plane.getClimbSpeed()) / 60;
}
void Route::setTOC()
{
    this->TOC = (descentDuration * plane.getCruisingSpeed()) / 60;
}
void Route::setCruiseAltitude()
{
    double ratio1 = plane.getClimbSpeed() / plane.getClimbRate();
    double ratio2 = plane.getCruisingSpeed() / plane.getDescentRate();
    double numerator = this->routeDistance * 60 + ratio1 * departure.getElevation() + ratio2 * arrival.getElevation();
    double denominator = ratio1 + ratio2;
    this->cruisingAltitude = (int) (numerator / denominator);
}
void Route::setAirTime()
{
    this->airTime = this->climbDuration + this->cruiseDuration + this->descentDuration;
}
void Route::setBlockTime()
{
    this->blockTime = this->airTime + 40; //40 minutes for taxi combined (departure + arrival)
}
bool Route::maxCruiseAltitudeExceeded() const {return this->cruisingAltitude > plane.getMaxCruisingAltitude();}
bool Route::terrainDanger() const
{
    for (const auto& waypct: waypoints)
        if (this->cruisingAltitude < waypct.getMinAltitude())
            return true;
    return false;
}
bool Route::flightTooShort() const{return this->airTime < plane.getMinimumFlightDuration();}
//bool Route::rwTooNarrowDepart() const {} those methods will be implemented soon
//bool Route::rwTooNarrowArrival() const{}
bool Route::rwTooShortDepar() const
{
    return this->plane.getPerfCalc().getTakeoffDistance() > this->departure.getRunway(departureRunway).getLength();
}
bool Route::rwTooShortArrival() const
{
    return this->plane.getPerfCalc().getLandingDistance() > this->arrival.getRunway(arrivalRunway).getLength();
}
bool Route::aircraftRangeExceeded() const
{
    return this->routeDistance > this->plane.getRange();
}
