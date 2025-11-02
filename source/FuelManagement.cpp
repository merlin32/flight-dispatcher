#include "../header/FuelManagement.h"

FuelManagement::FuelManagement(const double& contingencyPct_, const int& reserveTime_, const double& taxiFuel_, const double& blockFuel_)
{
    //contingencyPct value needs to be 0.1 if auto is selected in the route initialization
    if (contingencyPct_ != 0) this->contingencyPct = contingencyPct_;
    else this->contingencyPct = 0.1;
    //reserveTime value needs to be 30 if auto is selected in the route initialization
    if (reserveTime_ != 0) this->reserveTime = reserveTime_;
    else this->reserveTime = 30;
    //taxiFuel value can be inserted or calculated afterwards
    if (taxiFuel_ != 0) this->taxiFuel = taxiFuel_;
    else this->taxiFuel = 0;
    //same as taxiFuel
    if (blockFuel_ != 0) this->blockFuel = blockFuel_;
    else this->blockFuel = 0;
}
FuelManagement::FuelManagement(const FuelManagement& other) = default;
FuelManagement::FuelManagement(FuelManagement&& other) = default;
FuelManagement::~FuelManagement() = default;
void FuelManagement::setTripFuel(const double& climbDuration, const double& cruiseDuration, const double& descentDuration,
                 const double& fuelBurnClimb, const double& fuelBurnCruise, const double& fuelBurnDescent)
{
    this->tripFuel = climbDuration * fuelBurnClimb +
                     cruiseDuration * fuelBurnCruise+
                     descentDuration * fuelBurnDescent;
}
//contingencyFuel = extra fuel needed in case of any unwanted event
void FuelManagement::setContingencyFuel(){this->contingencyFuel = contingencyPct * this->tripFuel;}
//reserveFuel = the extra fuel the aircraft must have for this flight
void FuelManagement::setReserveFuel(const double& fuelBurnLowAltitude){this->reserveFuel = this->reserveTime * fuelBurnLowAltitude;}
//when taxiFuel is not inserted, we approximate that the taxi time takes around 20 minutes
void FuelManagement::setTaxiFuel(const double& fuelBurnIdle){this->taxiFuel = 20 * fuelBurnIdle;}
//setBlockFuel can be used when the blockFuel parameter isn't mentioned when creating the flight plan
void FuelManagement::setBlockFuel(){this->blockFuel = this->taxiFuel + this->tripFuel + this->contingencyFuel + this->reserveFuel + this->extraFuel;}
//setCalculatedFuel is being used when the blockFuel is mentioned and we need to check if the blockFuel is sufficient for the trip
void FuelManagement::setCalculatedBlockFuel(){this->calculatedBlockFuel = this->taxiFuel + this->tripFuel + this->contingencyFuel + this->reserveFuel + this->extraFuel;}
//when blockFuel is given, that value may be bigger than the necessary fuel to complete the trip -> extraFuel
void FuelManagement::setExtraFuel(){this->extraFuel = this->blockFuel - this->calculatedBlockFuel;}
void FuelManagement::setMinTakeoffFuel(){this->minimumTakeoffFuel = this->tripFuel + this->contingencyFuel + this->reserveFuel;}
void FuelManagement::setTakeoffFuel(){this->takeoffFuel = this->blockFuel - this->taxiFuel;}
//making sure that we have enough fuel to complete the trip
bool FuelManagement::isFuelSufficient() const{return this->calculatedBlockFuel > this->blockFuel;}
std::ostream& operator<<(std::ostream& os, const FuelManagement& flm)
{
    os << "============================\n";
    os << "===     PLANNED FUEL     ===\n";
    os << "============================\n";
    os << "TRIP: " << flm.tripFuel << '\n';
    os << "CONT " <<  flm.contingencyPct << " PCT: " << flm.contingencyFuel << '\n';
    os << "FINRES: " << flm.reserveFuel << '\n';
    os << "============================\n";
    os << "MINIMUM T/OFF FUEL: " << flm.minimumTakeoffFuel << '\n';
    os << "============================\n";
    os << "FOB ADD: " << flm.extraFuel << '\n';
    os << "============================\n";
    os << "T/OFF FUEL: " << flm.takeoffFuel << '\n';
    os << "TAXI: " << flm.taxiFuel << '\n';
    os << "============================\n";
    os << "BLOCK FUEL: " << flm.blockFuel << "\n\n";
    return os;
}



