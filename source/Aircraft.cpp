#include "../header/Aircraft.h"
#include <iostream>
#include <algorithm>
#include <nlohmann/json.hpp>

Aircraft::Aircraft()
{
    this->range = 0;
    this->cruisingSpeed = 0;
    this->wingSpan = 0;
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
             const double& wingSpan_,
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
          wingSpan{wingSpan_},
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
          minimumFlightDuration(minimumFlightDuration_){}
std::ostream& operator<<(std::ostream& os, const Aircraft& ac)
{
    os << "Category: " << ac.category << '\n';
    os << "Type: " << ac.type << '\n';
    os << "Range: " << ac.range << " NM\n";
    os << "Cruising Speed: " << ac.cruisingSpeed << " KTS\n";
    os << "Wing Span: " << ac.wingSpan << " M\n";
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
double Aircraft::calculateTaxiFuel() const{return 20 * fuelBurnIdle;}
bool Aircraft::fuelCapacityExceeded(const double& blockFuel) const {return blockFuel > fuelCapacity;}
bool Aircraft::maxPayloadExceeded(const double& payload) const {return payload > maxPayload;}
bool Aircraft::maxFreightExceeded(const double& freight) const {return freight > maxFreight;}
bool Aircraft::maxTakeoffWeightExceeded(const double& TOW) const{return TOW > maxTakeoffWeight;}
int Aircraft::getMaxCruisingAltitude() const {return this->maxCruisingAltitude;}
int Aircraft::getClimbRate() const {return this->climbRate;}
int Aircraft::getDescentRate() const {return this->descentRate;}
double Aircraft::getCruisingSpeed() const{return this->cruisingSpeed;}
double Aircraft::getClimbSpeed() const{return this->climbSpeed;}
int Aircraft::getMinimumFlightDuration() const{return this->minimumFlightDuration;}
double Aircraft::getRange() const{return this->range;}
std::string Aircraft::getType() const{return this->type;}
double Aircraft::getEmptyWeight() const{return this->emptyWeight;}
double Aircraft::getTakeoffReferenceDist() const{return this->takeoffReferenceDist;}
double Aircraft::getMaxTakeoffWeight() const{return this->maxTakeoffWeight;}
std::string Aircraft::getCategory() const {return this->category;}
//virtual functions calls
double Aircraft::calculateFreight() const{return calculateFreight_();}
double Aircraft::calculatePayload() const{return calculatePayload_();}
bool Aircraft::isDataValid() const {return isDataValid_();}
void Aircraft::readFromJson(const nlohmann::json& obj)
{
    category = obj["category"];
    type = obj["type"];
    range = obj["range"];
    cruisingSpeed = obj["cruisingSpeed"];
    wingSpan = obj["wingSpan"];
    maxTakeoffWeight = obj["maxTakeoffWeight"];
    maxPayload = obj["maxPayload"];
    emptyWeight = obj["emptyWeight"];
    fuelCapacity = obj["fuelCapacity"];
    fuelBurnClimb = obj["fuelBurnClimb"];
    fuelBurnCruise = obj["fuelBurnCruise"];
    fuelBurnDescent = obj["fuelBurnDescent"];
    maxCruisingAltitude = obj["maxCruisingAltitude"];
    fuelBurnIdle = obj["fuelBurnIdle"];
    fuelBurnLowAltitude = obj["fuelBurnLowAltitude"];
    maxFreight = obj["maxFreight"];
    takeoffReferenceDist = obj["takeoffReferenceDist"];
    climbRate = obj["climbRate"];
    descentRate = obj["descentRate"];
    climbSpeed = obj["climbSpeed"];
    minimumFlightDuration = obj["minimumFlightDuration"];
    readFromJson_(obj);
}
bool Aircraft::compareAircraftTypes(const std::shared_ptr<Aircraft>& plane1, const std::shared_ptr<Aircraft>& plane2)
{
    return plane1->getType() < plane2->getType();
}
bool Aircraft::validAircraft(const std::vector<std::shared_ptr<Aircraft>>& aircraftsList, const std::string& inputType,
                                std::shared_ptr<Aircraft>& plane)
{
    auto position = std::lower_bound(aircraftsList.begin(), aircraftsList.end(), inputType,
                                    [](const std::shared_ptr<Aircraft>& a, const std::string& tp)
                                    {
                                        return a->getType() < tp;
                                    });
    if (position != aircraftsList.end() && (*position)->getType() == inputType)
    {
        plane = *position;
        return true;
    }
    std::cerr << "Invalid aircraft type! Enter a valid aircraft type!\n";
    return false;
}










