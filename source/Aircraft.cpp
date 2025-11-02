#include "../header/Aircraft.h"

Aircraft::Aircraft(double range_,
             double cruisingSpeed_,
             double wingSpan_,
             double maxTakeoffWeight_,
             double maxPayload_,
             double emptyWeight_,
             double fuelCapacity_,
             double fuelBurnClimb_,
             double fuelBurnCruise_,
             double fuelBurnDescent_,
             int maxCruisingAltitude_,
             const FuelManagement& fuelPlanning_,
             const PerformanceCalculation& perfCalc_,
             double fuelBurnIdle_,
             double fuelBurnLowAltitude_,
             double maxFreight_,
             int maxPassengerCount_,
             double takeoffReferenceDist_,
             int climbRate_,
             int descentRate_,
             double climbSpeed_,
             int minimumFlightDuration_)
        : range{range_},
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
          fuelPlanning{fuelPlanning_},
          perfCalc{perfCalc_},
          fuelBurnIdle{fuelBurnIdle_},
          fuelBurnLowAltitude{fuelBurnLowAltitude_},
          maxFreight{maxFreight_},
          maxPassengerCount{maxPassengerCount_},
          takeoffReferenceDist{takeoffReferenceDist_},
          climbRate{climbRate_},
          descentRate{descentRate_},
          climbSpeed{climbSpeed_},
          minimumFlightDuration(minimumFlightDuration_){}
Aircraft::Aircraft(const Aircraft& other) = default;
Aircraft::~Aircraft() = default;
std::ostream& operator<<(std::ostream& os, const Aircraft& ac)
{
    os << "Range: " << ac.range << '\n';
    os << "Cruising Speed: " << ac.cruisingSpeed << '\n';
    os << "Wing Span: " << ac.wingSpan << '\n';
    os << "Maximum Takeoff Weight: " << ac.maxTakeoffWeight << '\n';
    os << "Maximum Payload: " << ac.maxPayload << '\n';
    os << "Empty Weight: " << ac.emptyWeight << '\n';
    os << "Fuel Capacity: " << ac.fuelCapacity << '\n';
    os << "Fuel Burn Climb: " << ac.fuelBurnClimb << '\n';
    os << "Fuel Burn Cruise: " << ac.fuelBurnCruise << '\n';
    os << "Fuel Burn Descent: " << ac.fuelBurnDescent << '\n';
    os << "Fuel Burn Idle: " << ac.fuelBurnIdle << '\n';
    os << "Fuel Burn Low Altitude: " << ac.fuelBurnLowAltitude << '\n';
    os << "Max Freight: " << ac.maxFreight << '\n';
    os << "Max Passenger Count: " << ac.maxPassengerCount << '\n';
    os << "Takeoff Reference Distance: " << ac.takeoffReferenceDist << '\n';
    os << "Climb Rate: " << ac.climbRate << '\n';
    os << "Descent Rate: " << ac.descentRate << '\n';
    os << "Climb Speed: " << ac.climbSpeed << '\n';
    os << "Minimum Flight Duration: " << ac.minimumFlightDuration << '\n';
    os << ac.fuelPlanning;
    os << ac.perfCalc;

    return os;
}
int Aircraft::getMaxCruisingAltitude() const {return this->maxCruisingAltitude;}
int Aircraft::getClimbRate() const {return this->climbRate;}
int Aircraft::getDescentRate() const {return this->descentRate;}
double Aircraft::getCruisingSpeed() const{return this->cruisingSpeed;}
double Aircraft::getClimbSpeed() const{return this->climbSpeed;}
int Aircraft::getMinimumFlightDuration() const{return this->minimumFlightDuration;}
PerformanceCalculation Aircraft::getPerfCalc() const{return this->perfCalc;}
double Aircraft::getRange() const{return this->range;}


