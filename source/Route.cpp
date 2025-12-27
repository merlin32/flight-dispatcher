#include "../header/Route.h"

Route::Route(const int& cruisingAltitude_, std::string flightNumber_, std::string callsign_,
                    const Airport& departure_, const Airport& arrival_, std::string departureRunway_, std::string arrivalRunway_,
                    const std::vector<Waypoint>& waypoints_, std::shared_ptr<Aircraft> plane_,
                    const FuelManagement& fuelPlanning_, const PerformanceCalculation& perfCalc_):
                    cruisingAltitude{cruisingAltitude_}, flightNumber{std::move(flightNumber_)}, callsign{std::move(callsign_)},
                    departure{departure_}, arrival{arrival_}, departureRunway{std::move(departureRunway_)},
                    arrivalRunway{std::move(arrivalRunway_)}, waypoints{std::move(waypoints_)}, plane{std::move(plane_)},
                    fuelPlanning{fuelPlanning_}, perfCalc{perfCalc_}{}
Route::Route(const Route& other) : cruisingAltitude{other.cruisingAltitude},
                    flightNumber{other.flightNumber},
                    callsign{other.callsign},
                    departure{other.departure},
                    arrival{other.arrival},
                    departureRunway{other.departureRunway},
                    arrivalRunway{other.arrivalRunway},
                    waypoints{other.waypoints},
                    plane{other.plane},
                    fuelPlanning{other.fuelPlanning},
                    perfCalc{other.perfCalc}{}
Route& Route::operator=(Route other)
{
    if (this != &other)
        swap(*this, other);
    return *this;
}
void swap(Route& rt1, Route& rt2) noexcept
{
    using std::swap;
    swap(rt1.cruisingAltitude, rt2.cruisingAltitude);
    swap(rt1.routeDistance, rt2.routeDistance);
    swap(rt1.flightNumber, rt2.flightNumber);
    swap(rt1.callsign, rt2.callsign);
    swap(rt1.departureRunway, rt2.departureRunway);
    swap(rt1.arrivalRunway, rt2.arrivalRunway);
    swap(rt1.blockTime, rt2.blockTime);
    swap(rt1.airTime, rt2.airTime);
    swap(rt1.climbDuration, rt2.climbDuration);
    swap(rt1.cruiseDuration, rt2.cruiseDuration);
    swap(rt1.descentDuration, rt2.descentDuration);
    swap(rt1.TOC, rt2.TOC);
    swap(rt1.TOD, rt2.TOD);
    swap(rt1.departure, rt2.departure);
    swap(rt1.arrival, rt2.arrival);
    swap(rt1.waypoints, rt2.waypoints);
    swap(rt1.plane, rt2.plane);
    swap(rt1.fuelPlanning, rt2.fuelPlanning);
    swap(rt1.perfCalc, rt2.perfCalc);
}
void Route::setRouteDistance()
{
    for (const auto& waypct : waypoints)
        this->routeDistance += waypct.getDistanceToPrevious();
}
void Route::setClimbDuration()
{
    this->climbDuration = (double)(this->cruisingAltitude - this->departure.getElevation()) / plane->getClimbRate();
}
void Route::setCruiseDuration()
{
    this->cruiseDuration = (this->TOD - this->TOC) / plane->getCruisingSpeed();
}
void Route::setDescentDuration()
{
    this->descentDuration = (double)(this->cruisingAltitude - arrival.getElevation()) / plane->getDescentRate();
}
void Route::setTOD()
{
    this->TOD = (descentDuration * plane->getCruisingSpeed()) / 60;
}
void Route::setTOC()
{
    this->TOC = (climbDuration * plane->getClimbSpeed()) / 60;
}
void Route::setCruiseAltitude()
{
    double ratio1 = plane->getClimbSpeed() / plane->getClimbRate();
    double ratio2 = plane->getCruisingSpeed() / plane->getDescentRate();
    double numerator = this->routeDistance * 60 + ratio1 * departure.getElevation() + ratio2 * arrival.getElevation();
    double denominator = ratio1 + ratio2;
    this->cruisingAltitude = (int) (numerator / denominator);
    while (plane->getMaxCruisingAltitude() < cruisingAltitude && cruisingAltitude > 4000)
        cruisingAltitude -= 1000;
}
void Route::setAirTime()
{
    this->airTime = this->climbDuration + this->cruiseDuration + this->descentDuration;
}
void Route::setBlockTime()
{
    this->blockTime = this->airTime + 40; //40 minutes for taxi combined (departure + arrival)
}
bool Route::maxCruiseAltitudeExceeded() const {return this->cruisingAltitude > plane->getMaxCruisingAltitude();}
bool Route::terrainDanger() const
{
    for (const auto& waypct: waypoints)
        if (this->cruisingAltitude < waypct.getMinAltitude())
            return true;
    return false;
}
bool Route::flightTooShort() const{return this->airTime < plane->getMinimumFlightDuration();}
//bool Route::rwTooNarrowDepart() const {} those methods will be implemented soon
//bool Route::rwTooNarrowArrival() const{}
bool Route::rwTooShortDepar() const
{
    return this->perfCalc.getTakeoffDistance() > this->departure.getRunway(departureRunway).getLength();
}
bool Route::rwTooShortArrival() const
{
    return this->perfCalc.getLandingDistance() > this->arrival.getRunway(arrivalRunway).getLength();
}
bool Route::aircraftRangeExceeded() const
{
    return this->routeDistance > this->plane->getRange();
}
bool Route::getCruisingAltitude() const
{
    return this->cruisingAltitude;
}

bool Route::routeInit()
{
    this->setRouteDistance();
    if (cruisingAltitude == 0)
        this->setCruiseAltitude();
    if (this->maxCruiseAltitudeExceeded() == true)
    {
        std::cerr << "Cruise altitude exceeds aircraft's maximum cruising altitude!\n";
        return false;
    }
    this->setClimbDuration();
    this->setDescentDuration();
    this->setTOC();
    this->setTOD();
    this->setCruiseDuration();
    this->setAirTime();
    this->setBlockTime();
    if (this->flightTooShort() == true)
    {
        std::cerr << "Flight duration is too short for the selected aircraft!\n";
        return false;
    }
    if (this->terrainDanger() == true)
    {
        std::cerr << "Impossible to create the flight plan: cruising altitude is below waypoint minimum!\n";
        return false;
    }
    if (this->rwTooShortDepar() == true)
    {
        std::cerr << "Selected departure runway is too short for this configuration!\n";
        return false;
    }
    if (this->rwTooShortArrival() == true)
    {
        std::cerr << "Selected arrival runway is too short for this configuration!\n";
        return false;
    }
    if (this->aircraftRangeExceeded() == true)
    {
        std::cerr << "Flight exceeds the range of the selected aircraft!\n";
        return false;
    }
    if (this->fuelPlanning.init(this->climbDuration, this->cruiseDuration, this->descentDuration, this->plane) == false)
    {
        std::cerr << "Invalid fuel data!\n";
        return false;
    }
    if (this->perfCalc.init(plane, fuelPlanning, departure, arrival, arrivalRunway) == false)
    {
        std::cerr << "Invalid payload data!\n";
        return false;
    }
    return true;
}
std::ostream& operator<<(std::ostream& os, const Route& rt)
{
    os << "=========================\n";
    os << "== Flight plan details ==\n";
    os << "=========================\n";
    os << "Flight number: " << rt.flightNumber << "\n";
    os << "Callsign: " << rt.callsign << "\n";
    os << "Departure: " << rt.departure.getIcao() << " (Runway: " << rt.departureRunway << ")\n";
    os << "Arrival: " << rt.arrival.getIcao() << " (Runway: " << rt.arrivalRunway << ")\n";
    os << "Cruising altitude: " << rt.cruisingAltitude << " FT\n";
    os << "Route distance: " << rt.routeDistance << " NM\n";
    os << "Block time: " << rt.blockTime << " MIN\n";
    os << "Air time: " << rt.airTime << " MIN\n";
    os << "Climb duration: " << rt.climbDuration << " MIN\n";
    os << "Cruise duration: " << rt.cruiseDuration << " MIN\n";
    os << "Descent duration: " << rt.descentDuration << " MIN\n";
    os << "TOC: " << rt.TOC << " NM\n";
    os << "TOD: " << rt.TOD << " NM\n";
    os << "Plane:\n" << *rt.plane << "\n";
    os << rt.fuelPlanning << "\n";
    os << rt.perfCalc << "\n";

    os << "Route:\n";
    for (size_t i = 0; i < rt.waypoints.size(); ++i) {
        os << rt.waypoints[i].getWaypointCode();
        if (i != rt.waypoints.size() - 1)
            os << " DCT ";
    }
    os << '\n';
    return os;
}
