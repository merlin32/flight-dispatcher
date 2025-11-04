#include "../header/Route.h"

Route::Route(const int& cruisingAltitude_, const std::string& flightNumber_, const std::string& callsign_,
                    const Airport& departure_, const Airport& arrival_, const std::string& departureRunway_, const std::string& arrivalRunway_,
                    const std::vector<Waypoint>& waypoints_, const Aircraft& plane_,
                    const FuelManagement& fuelPlanning_, const PerformanceCalculation& perfCalc_):
                    cruisingAltitude{cruisingAltitude_}, flightNumber{flightNumber_}, callsign{callsign_},
                    departure{departure_}, arrival{arrival_}, departureRunway{departureRunway_},
                    arrivalRunway{arrivalRunway_}, waypoints{waypoints_}, plane{plane_},
                    fuelPlanning{fuelPlanning_}, perfCalc{perfCalc_}{}
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
    this->TOD = (descentDuration * plane.getCruisingSpeed()) / 60;
}
void Route::setTOC()
{
    this->TOC = (climbDuration * plane.getClimbSpeed()) / 60;
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
    return this->perfCalc.getTakeoffDistance() > this->departure.getRunway(departureRunway).getLength();
}
bool Route::rwTooShortArrival() const
{
    return this->perfCalc.getLandingDistance() > this->arrival.getRunway(arrivalRunway).getLength();
}
bool Route::aircraftRangeExceeded() const
{
    return this->routeDistance > this->plane.getRange();
}
bool Route::getCruisingAltitude() const
{
    return this->cruisingAltitude;
}

bool Route::routeInit()
{
    this->setRouteDistance();
    if (this->getCruisingAltitude() == 0)
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
    return true;
}
bool Route::fuelManagementInit()
{
    this->fuelPlanning.setTripFuel(this->climbDuration, this->cruiseDuration, this->descentDuration,
                                   this->plane.getFuelBurnClimb(), this->plane.getFuelBurnCruise(),
                                   this->plane.getFuelBurnDescent());
    this->fuelPlanning.setContingencyFuel();
    this->fuelPlanning.setReserveFuel(this->plane.getFuelBurnLowAltitude());
    if (this->fuelPlanning.getTaxiFuel() == 0)
        this->fuelPlanning.setTaxiFuel(this->plane.getFuelBurnIdle());
    if (this->fuelPlanning.getBlockFuel() == 0)
    {
        this->fuelPlanning.setBlockFuel();
        this->fuelPlanning.setCalculatedBlockFuel();
        this->fuelPlanning.setExtraFuel();
    }
    else
    {
        this->fuelPlanning.setCalculatedBlockFuel();
        if (this->fuelPlanning.isFuelSufficient() == false)
        {
            std::cerr << "Inserted block fuel is invalid: not enough fuel to complete the trip!\n";
            return false;
        }
    }
    this->fuelPlanning.setExtraFuel();
    this->fuelPlanning.setMinTakeoffFuel();
    this->fuelPlanning.setTakeoffFuel();
    if (this->fuelPlanning.fuelCapacityExceeded(this->plane.getFuelCapacity()) == true)
    {
        std::cerr << "Block fuel exceeds aircraft's maximum fuel capacity!\n";
        return false;
    }
    return true;
}
bool Route::performanceCalculationInit()
{
    if (this->perfCalc.maxPassengersExceeded(this->plane.getMaxPassengerCount()))
    {
        std::cerr << "Passengers number has been exceeded!\n";
        return false;
    }
    if (this->perfCalc.maxFreightExceeded(this->plane.getMaxFreight()) == true)
    {
        std::cerr << "Maximum freight value has been exceeded!\n";
        return false;
    }
    this->perfCalc.setPayload();
    if (this->perfCalc.getFreight() == 0)
        this->perfCalc.setFreight();
    this->perfCalc.setZFW(this->plane.getEmptyWeight());
    this->perfCalc.setTOW(this->fuelPlanning.getBlockFuel(), this->fuelPlanning.getTaxiFuel());
    this->perfCalc.setLDW(this->fuelPlanning.getTripFuel());
    this->perfCalc.setTotalWeight(this->fuelPlanning.getBlockFuel());
    this->perfCalc.setTakeoffDistance(this->plane.getTakeoffReferenceDist(),
                                      this->plane.getMaxTakeoffWeight(),
                                      this->departure.getWeather().getMetar().getQnh(),
                                      this->departure.getWeather().getMetar().getTemperature());
    this->perfCalc.setLandingDistance(this->plane.getTakeoffReferenceDist(), this->plane.getMaxTakeoffWeight(),
                                      this->arrival.getWeather().getMetar().getQnh(),
                                      this->arrival.getWeather().getMetar().getTemperature(),
                                      this->arrival.getWeather().getMetar().getWindSpeed(),
                                      this->arrival.getWeather().getMetar().getWindDirection(),
                                      this->arrival.getRunway(arrivalRunway).getRwDirection(),
                                      this->arrival.getRunway(arrivalRunway).getRwCondition());
    if (this->perfCalc.maxPayloadExceeded(this->plane.getMaxPayload()) == true)
    {
        std::cerr << "Maximum payload value has been exceeded!\n";
        return false;
    }
    if (this->perfCalc.maxTakeoffWeightExceeded(this->plane.getMaxTakeoffWeight()) == true)
    {
        std::cerr << "Maximum takeoff weight value has been exceeded!\n";
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
    os << "Plane:\n" << rt.plane << "\n";
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
