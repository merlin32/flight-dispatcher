#include "../header/PassengerAircraft.h"

PassengerAircraft::PassengerAircraft(const std::string& type_,
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
             const int& minimumFlightDuration_,
             const int& maxPassengerCount_,
             const int& crewCount_) : Aircraft{type_, range_, cruisingSpeed_,
             wingSpan_, maxTakeoffWeight_, maxPayload_, emptyWeight_, fuelCapacity_,
             fuelBurnClimb_, fuelBurnCruise_, fuelBurnDescent_, maxCruisingAltitude_,
             fuelBurnIdle_, fuelBurnLowAltitude_, maxFreight_, takeoffReferenceDist_,
             climbRate_, descentRate_, climbSpeed_, minimumFlightDuration_}, maxPassengerCount{maxPassengerCount_},
             crewCount{crewCount_} {}
std::shared_ptr<Aircraft> PassengerAircraft::clone() const override {return std::make_shared<PassengerAircraft>(*this);}
void PassengerAircraft::setFreight(const int& inputFreight){ this->freight = inputFreight;}
void PassengerAircraft::setPassengerNumber(const int& inputPassengerNumber){this->passengerNumber = inputPassengerNumber;}
//on average, a person is estimated to weight around 75 kg
double PassengerAircraft::calculatePayload_() const override {return 75 * (passengerNumber + crewCount) + freight;}
//on average, a person is estimated to have 10kg of baggage
double PassengerAircraft::calculateFreight_() const override {return 10 * (passengerNumber + crewCount);}
bool PassengerAircraft::maxPassengersExceeded() const {return passengerNumber > maxPassengerCount;}
void PassengerAircraft::display(std::ostream &os) const override
{
    os << "Maximum passenger capacity: " << maxPassengerCount << '\n';
    os << "Crew count: " << crewCount << '\n';
}




