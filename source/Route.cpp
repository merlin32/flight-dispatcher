#include "../header/Route.h"
#include "../header/Exceptions.h"

Route::Route(std::string callsign_,
             const Airport& departure_, const Airport& arrival_, std::string departureRunway_, std::string arrivalRunway_,
             const std::vector<Waypoint>& waypoints_, std::shared_ptr<Aircraft> plane_,
             const FuelManagement& fuelPlanning_, const PerformanceCalculation& perfCalc_,
             const int& cruisingAltitude_ = 1000):
                    callsign{std::move(callsign_)},
                    departure{departure_}, arrival{arrival_}, departureRunway{std::move(departureRunway_)},
                    arrivalRunway{std::move(arrivalRunway_)}, waypoints{std::move(waypoints_)}, plane{std::move(plane_)},
                    fuelPlanning{fuelPlanning_}, perfCalc{perfCalc_}, cruisingAltitude{cruisingAltitude_}
{
    if (callsign.empty()) throw InvalidObjectCreation("Route", "callsign");
    if (departureRunway.empty()) throw InvalidObjectCreation("Route", "departureRunway");
    if (arrivalRunway.empty()) throw InvalidObjectCreation("Route", "arrivalRunway");
}
Route::Route(const Route& other) :
                    callsign{other.callsign},
                    departure{other.departure},
                    arrival{other.arrival},
                    departureRunway{other.departureRunway},
                    arrivalRunway{other.arrivalRunway},
                    waypoints{other.waypoints},
                    plane{other.plane},
                    fuelPlanning{other.fuelPlanning},
                    perfCalc{other.perfCalc},
                    cruisingAltitude{other.cruisingAltitude}
{
    routeDistance = other.routeDistance;
    blockTime = other.blockTime;
    airTime = other.airTime;
    climbDuration = other.climbDuration;
    cruiseDuration = other.cruiseDuration;
    descentDuration = other.descentDuration;
    TOC = other.TOC;
    TOD = other.TOD;
}
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
    for (auto i = waypoints.begin(); i != waypoints.end() - 1; i++)
        this->routeDistance += Waypoint::calculateDistance(*i, *(i + 1));
}
void Route::setClimbDuration()
{
    double delta = this->cruisingAltitude - this->departure.getElevation();
    this->climbDuration = plane->calculateClimbDuration(delta);
}
void Route::setCruiseDuration()
{
    double delta = TOD - TOC;
    this->cruiseDuration = plane->calculateCruiseDuration(delta);
}
void Route::setDescentDuration()
{
    double delta = this->cruisingAltitude - arrival.getElevation();
    this->descentDuration = plane->calculateDescentDuration(delta);
}
void Route::setTOD()
{
    double descentDistance = plane->distanceWhileDescending(descentDuration);
    this->TOD = routeDistance - descentDistance;
}
void Route::setTOC()
{
    this->TOC = plane->distanceWhileClimbing(climbDuration);
}
void Route::setCruiseAltitude()
{
    double ratio1 = plane->climbSpeedVsRateRatio();
    double ratio2 = plane->cruiseSpeedVsDescentRateRatio();
    double numerator = this->routeDistance * 60 + ratio1 * departure.getElevation() + ratio2 * arrival.getElevation();
    double denominator = ratio1 + ratio2;
    this->cruisingAltitude = (int) (numerator / denominator);
    while (plane->maxCruiseAltitudeExceeded(cruisingAltitude) && cruisingAltitude > MINIMUM_CRUISE_ALT)
        cruisingAltitude -= ALT_DECREMENT;
}
void Route::setAirTime()
{
    this->airTime = this->climbDuration + this->cruiseDuration + this->descentDuration;
}
void Route::setBlockTime()
{
    this->blockTime = this->airTime + Aircraft::calculateDefaultTaxiTime(); //40 minutes for taxi combined (departure + arrival)
}
bool Route::terrainDanger() const
{
    for (const auto& waypct: waypoints)
        if (waypct.belowMinAlt(this->cruisingAltitude) == true)
            return true;
    return false;
}
bool Route::rwTooShortDepar() const
{
    return this->departure.getRunway(departureRunway).runwayTooShortTakeoff(this->perfCalc.getTakeoffDistance());
}
bool Route::rwTooShortArrival() const
{
    return this->arrival.getRunway(arrivalRunway).runwayTooShortLanding(this->perfCalc.getLandingDistance());
}
void Route::routeInit()
{
    this->setRouteDistance();
    if (cruisingAltitude == 0)
        this->setCruiseAltitude();
    this->setClimbDuration();
    this->setDescentDuration();
    this->setTOC();
    this->setTOD();
    this->setCruiseDuration();
    this->setAirTime();
    this->setBlockTime();
    if (this->plane->flightTooShort(airTime) == true)
        throw InvalidFlightPlanParameters("Flight duration is too short for the selected aircraft!");
    if (this->terrainDanger() == true)
        throw InvalidFlightPlanParameters("Impossible to create the flight plan: cruising altitude is below waypoint minimum!");
    if (this->rwTooShortDepar() == true)
        throw InvalidFlightPlanParameters("Selected departure runway is too short for this configuration!");
    if (this->rwTooShortArrival() == true)
        throw InvalidFlightPlanParameters("Selected arrival runway is too short for this configuration!");
    if (this->plane->aircraftRangeExceeded(routeDistance) == true)
        throw InvalidFlightPlanParameters("Flight exceeds the range of the selected aircraft!");
    if (this->plane->aircraftTooWide(this->departure.getRunway(departureRunway).getWidth()))
        throw InvalidFlightPlanParameters("Aircraft too wide for the departure runway!");
    if (this->plane->aircraftTooWide(this->arrival.getRunway(arrivalRunway).getWidth()))
        throw InvalidFlightPlanParameters("Aircraft too wide for the arrival runway!");
    this->fuelPlanning.init(this->climbDuration, this->cruiseDuration, this->descentDuration, this->plane);
    this->perfCalc.init(plane, fuelPlanning, departure, arrival, arrivalRunway);
}
std::ostream& operator<<(std::ostream& os, const Route& rt)
{
    os << "=========================\n";
    os << "== Flight plan details ==\n";
    os << "=========================\n";
    os << "CALLSIGN: " << rt.callsign << "\n";
    os << "DEPARTURE: ";
    rt.departure.displayIcaoCode();
    os << " (RUNWAY: " << rt.departureRunway << ")\n";
    os << "ARRIVAL: ";
    rt.arrival.displayIcaoCode();
    os << " (RUNWAY: " << rt.arrivalRunway << ")\n";
    os << "CRUISING ALTITUDE: " << rt.cruisingAltitude << " FT\n";
    os << "ROUTE DISTANCE: " << rt.routeDistance << " NM\n";
    os << "BLOCK TIME: " << rt.blockTime << " MIN\n";
    os << "AIR TIME: " << rt.airTime << " MIN\n";
    os << "CLIMB DURATION: " << rt.climbDuration << " MIN\n";
    os << "CRUISE DURATION: " << rt.cruiseDuration << " MIN\n";
    os << "DESCENT DURATION: " << rt.descentDuration << " MIN\n";
    os << "TOC: " << rt.TOC << " NM\n";
    os << "TOD: " << rt.TOD << " NM\n\n";
    os << "=========================\n";
    os << "===== Plane Details =====\n";
    os << "=========================\n";
    os << *rt.plane << "\n";
    os << rt.fuelPlanning << "\n";
    os << rt.perfCalc << "\n";

    os << "ROUTE:\n";
    for (size_t i = 0; i < rt.waypoints.size(); ++i) {
        rt.waypoints[i].displayWaypointCode();
        if (i != rt.waypoints.size() - 1)
            os << " DCT ";
    }
    os << "\n\n";
    os << "METAR INFO: \n";
    os << "\tDEPARTURE: ";
    rt.departure.displayMetar();
    os << '\n';
    os << "\tARRIVAL: ";
    rt.arrival.displayMetar();
    os << '\n';
    return os;
}
void Route::displayShortInfo() const
{
    departure.displayIcaoCode();
    std::cout << " - ";
    arrival.displayIcaoCode();
    std::cout << ": ";
    plane->displayAircraftType();
    std::cout << '\n';
}

