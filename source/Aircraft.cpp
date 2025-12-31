#include "../header/Aircraft.h"
#include <iostream>
#include <algorithm>
#include <nlohmann/json.hpp>

#include "../header/Exceptions.h"
#include "../header/JsonUtils.h"

Aircraft::Aircraft()
{
    this->range = 0;
    this->cruisingSpeed = 0;
    this->wingspan = 0;
    this->maxTakeoffWeight = 0;
    this->maxPayload = 0;
    this->emptyWeight = 0;
    this->fuelCapacity = 0;
    this->fuelBurnClimb = 0;
    this->fuelBurnCruise = 0;
    this->fuelBurnDescent = 0;
    this->maxCruisingAltitude = 0;
    this->fuelBurnIdle = 0;
    this->fuelBurnLowAltitude = 0;
    this->maxFreight = 0;
    this->takeoffReferenceDist = 0;
    this->climbRate = 0;
    this->descentRate = 0;
    this->climbSpeed = 0;
    this->minimumFlightDuration = 0;
}
Aircraft::Aircraft(std::string category_,
             std::string type_,
             const double& range_,
             const double& cruisingSpeed_,
             const double& wingspan_,
             const double& maxTakeoffWeight_,
             const double& maxPayload_,
             const double& emptyWeight_,
             const double& fuelCapacity_,
             const double& fuelBurnClimb_,
             const double& fuelBurnCruise_,
             const double& fuelBurnDescent_,
             const int& maxCruisingAltitude_,
             const double& fuelBurnIdle_,
             const double& fuelBurnLowAltitude_,
             const double& maxFreight_,
             const double& takeoffReferenceDist_,
             const int& climbRate_,
             const int& descentRate_,
             const double& climbSpeed_,
             const int& minimumFlightDuration_)
        : category{std::move(category_)},
          type{std::move(type_)},
          range{range_},
          cruisingSpeed{cruisingSpeed_},
          wingspan{wingspan_},
          maxTakeoffWeight{maxTakeoffWeight_},
          maxPayload{maxPayload_},
          emptyWeight{emptyWeight_},
          fuelCapacity{fuelCapacity_},
          fuelBurnClimb{fuelBurnClimb_},
          fuelBurnCruise{fuelBurnCruise_},
          fuelBurnDescent{fuelBurnDescent_},
          maxCruisingAltitude{maxCruisingAltitude_},
          fuelBurnIdle{fuelBurnIdle_},
          fuelBurnLowAltitude{fuelBurnLowAltitude_},
          maxFreight{maxFreight_},
          takeoffReferenceDist{takeoffReferenceDist_},
          climbRate{climbRate_},
          descentRate{descentRate_},
          climbSpeed{climbSpeed_},
          minimumFlightDuration(minimumFlightDuration_)
{
    attributeValidation(category, "category");
    attributeValidation(type, "category");
    attributeValidation(range, "range");
    attributeValidation(cruisingSpeed, "cruisingSpeed");
    attributeValidation(wingspan, "wingspan");
    attributeValidation(maxTakeoffWeight, "maxTakeoffWeight");
    attributeValidation(maxPayload, "maxPayload");
    attributeValidation(emptyWeight, "emptyWeight");
    attributeValidation(fuelCapacity, "fuelCapacity");
    attributeValidation(fuelBurnClimb, "fuelBurnClimb");
    attributeValidation(fuelBurnCruise, "fuelBurnCruise");
    attributeValidation(fuelBurnDescent, "fuelBurnDescent");
    attributeValidation(maxCruisingAltitude, "maxCruisingAltitude");
    attributeValidation(fuelBurnIdle, "fuelBurnIdle");
    attributeValidation(fuelBurnLowAltitude, "fuelBurnLowAltitude");
    attributeValidation(maxFreight, "maxFreight");
    attributeValidation(takeoffReferenceDist, "takeoffReferenceDist");
    attributeValidation(climbRate, "climbRate");
    attributeValidation(descentRate, "descentRate");
    attributeValidation(climbSpeed, "climbSpeed");
    attributeValidation(minimumFlightDuration, "minimumFlightDuration");
}
std::ostream& operator<<(std::ostream& os, const Aircraft& ac)
{
    os << "Category: " << ac.category << '\n';
    os << "Type: " << ac.type << '\n';
    os << "Range: " << ac.range << " NM\n";
    os << "Cruising Speed: " << ac.cruisingSpeed << " KTS\n";
    os << "Wing Span: " << ac.wingspan << " M\n";
    os << "Maximum Takeoff Weight: " << ac.maxTakeoffWeight << " KG\n";
    os << "Maximum Payload: " << ac.maxPayload << " KG\n";
    os << "Empty Weight: " << ac.emptyWeight << " KG\n";
    os << "Fuel Capacity: " << ac.fuelCapacity << " KG\n";
    os << "Fuel Burn Climb: " << ac.fuelBurnClimb << " KG/MIN\n";
    os << "Fuel Burn Cruise: " << ac.fuelBurnCruise << " KG/MIN\n";
    os << "Fuel Burn Descent: " << ac.fuelBurnDescent << " KG/MIN\n";
    os << "Fuel Burn Idle: " << ac.fuelBurnIdle << " KG/MIN\n";
    os << "Fuel Burn Low Altitude: " << ac.fuelBurnLowAltitude << " KG/MIN\n";
    os << "Max Freight: " << ac.maxFreight << " KG\n";
    os << "Takeoff Reference Distance: " << ac.takeoffReferenceDist << " M\n";
    os << "Climb Rate: " << ac.climbRate << " FT/MIN\n";
    os << "Descent Rate: " << ac.descentRate << " FT/MIN\n";
    os << "Climb Speed: " << ac.climbSpeed << " KTS\n";
    os << "Minimum Flight Duration: " << ac.minimumFlightDuration << " MIN\n";
    ac.display(os);
    os << '\n';
    return os;
}
double Aircraft::calculateTripFuel(const double& climbDuration, const double& cruiseDuration,
                                    const double& descentDuration, const double& TOW) const
{
    //introducing a weight factor to compute the fuel consumption taking into account the takeoff weight as well
    double weightFactor = std::pow(TOW / maxTakeoffWeight, 0.75);
        return (climbDuration * fuelBurnClimb +
                cruiseDuration * fuelBurnCruise +
                descentDuration * fuelBurnDescent) * weightFactor;
}
//reserveFuel = the extra fuel the aircraft must have for this flight
double Aircraft::calculateReserveFuel (const int& reserveTime)const{return reserveTime * fuelBurnLowAltitude;}
//when taxiFuel is not inserted, we approximate that the taxi time takes around 20 minutes
double Aircraft::calculateTaxiFuel() const{return TAXI_TIME_DURATION * fuelBurnIdle;}
//durations calculation
double Aircraft::calculateClimbDuration(const double& delta) const{return delta / climbRate;}
double Aircraft::calculateCruiseDuration(const double& delta) const{return 60 * delta / cruisingSpeed;}
double Aircraft::calculateDescentDuration(const double& delta) const{return delta / descentRate;}
double Aircraft::distanceWhileClimbing(const double& climbDuration) const{return climbDuration * climbSpeed / 60;}
double Aircraft::distanceWhileDescending(const double& descentDuration) const{return descentDuration * cruisingSpeed / 60;}
//ratio functions
double Aircraft::climbSpeedVsRateRatio() const{return climbSpeed / climbRate;}
double Aircraft::cruiseSpeedVsDescentRateRatio() const{return cruisingSpeed / descentRate;}
//block taxi time
int Aircraft::calculateDefaultTaxiTime() {return 2 * TAXI_TIME_DURATION;}
//check functions
bool Aircraft::fuelCapacityExceeded(const double& blockFuel) const {return blockFuel > fuelCapacity;}
bool Aircraft::maxPayloadExceeded(const double& payload) const {return payload > maxPayload;}
bool Aircraft::maxFreightExceeded(const double& freight) const {return freight > maxFreight;}
bool Aircraft::maxTakeoffWeightExceeded(const double& TOW) const{return TOW > maxTakeoffWeight;}
bool Aircraft::maxCruiseAltitudeExceeded(const int& cruiseAltitude) const {return cruiseAltitude > maxCruisingAltitude;}
bool Aircraft::flightTooShort(const double& airTime) const {return airTime < minimumFlightDuration;}
bool Aircraft::aircraftRangeExceeded(const double& routeDistance) const{return routeDistance > range;}
bool Aircraft::categoryMatch(const std::string& currentCategory) const{return currentCategory == category;}
bool Aircraft::aircraftTooWide(const double& runwayWidth) const{return runwayWidth < wingspan * RUNWAY_WIDTH_PCT;}
//getters
double Aircraft::getEmptyWeight() const{return this->emptyWeight;}
double Aircraft::getTakeoffReferenceDist() const{return this->takeoffReferenceDist;}
double Aircraft::getMaxTakeoffWeight() const{return this->maxTakeoffWeight;}
//virtual functions calls
double Aircraft::calculateFreight() const{return calculateFreight_();}
double Aircraft::calculatePayload() const{return calculatePayload_();}
//validations
bool Aircraft::isDataValid() const {return isDataValid_();}
void Aircraft::readFromJson(const nlohmann::json& obj)
{
    category = readAttribute<std::string>(obj, "category");
    type = readAttribute<std::string>(obj, "type");
    range = readAttribute<double>(obj, "range");
    cruisingSpeed = readAttribute<double>(obj, "cruisingSpeed");
    wingspan = readAttribute<double>(obj, "wingspan");
    maxTakeoffWeight = readAttribute<double>(obj, "maxTakeoffWeight");
    maxPayload = readAttribute<double>(obj, "maxPayload");
    emptyWeight = readAttribute<double>(obj, "emptyWeight");
    fuelCapacity = readAttribute<double>(obj, "fuelCapacity");
    fuelBurnClimb = readAttribute<double>(obj, "fuelBurnClimb");
    fuelBurnCruise = readAttribute<double>(obj, "fuelBurnCruise");
    fuelBurnDescent = readAttribute<double>(obj, "fuelBurnDescent");
    maxCruisingAltitude = readAttribute<int>(obj, "maxCruisingAltitude");
    fuelBurnIdle = readAttribute<double>(obj, "fuelBurnIdle");
    fuelBurnLowAltitude = readAttribute<double>(obj, "fuelBurnLowAltitude");
    maxFreight = readAttribute<double>(obj, "maxFreight");
    takeoffReferenceDist = readAttribute<double>(obj, "takeoffReferenceDist");
    climbRate = readAttribute<int>(obj, "climbRate");
    descentRate = readAttribute<int>(obj, "descentRate");
    climbSpeed = readAttribute<double>(obj, "climbSpeed");
    minimumFlightDuration = readAttribute<int>(obj, "minimumFlightDuration");
    readFromJson_(obj);
}
bool Aircraft::compareAircraftTypes(const std::shared_ptr<Aircraft>& plane1, const std::shared_ptr<Aircraft>& plane2)
{
    return plane1->type < plane2->type;
}
bool Aircraft::validAircraft(const std::vector<std::shared_ptr<Aircraft>>& aircraftsList, const std::string& inputType,
                                std::shared_ptr<Aircraft>& plane)
{
    auto position = std::lower_bound(aircraftsList.begin(), aircraftsList.end(), inputType,
                                    [](const std::shared_ptr<Aircraft>& a, const std::string& tp)
                                    {
                                        return a->type < tp;
                                    });
    if (position != aircraftsList.end() && (*position)->type == inputType)
    {
        plane = *position;
        return true;
    }
    std::cerr << "Invalid aircraft type! Enter a valid aircraft type!\n";
    return false;
}
void Aircraft::attributeValidation(const std::string& value, const std::string& attributeName)
{
    if (value.empty())
        throw InvalidObjectCreation("Aircraft", attributeName);
}
void Aircraft::attributeValidation(const double& value, const std::string& attributeName)
{
    if (value < 0)
        throw InvalidObjectCreation("Aircraft", attributeName);
}
void Aircraft::attributeValidation(const int& value, const std::string& attributeName)
{
    if (value < 0)
        throw InvalidObjectCreation("Aircraft", attributeName);
}
//others
void Aircraft::displayAircraftType() {std::cout << type;}














