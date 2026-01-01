#include "../header/FuelManagement.h"
#include <iostream>

#include "../header/Exceptions.h"

FuelManagement::FuelManagement(const double& contingencyPct_, const int& reserveTime_, const double& taxiFuel_, const double& blockFuel_)
{
    //contingencyPct value needs to be 0.1 if auto is selected in the route initialization
    if (contingencyPct_ > 0) this->contingencyPct = contingencyPct_;
    else if (contingencyPct_ == 0) this->contingencyPct = 0.1;
    if (contingencyPct < 0) throw InvalidObjectCreation("FuelManagement", "contingencyPct");
    //reserveTime value needs to be 30 if auto is selected in the route initialization
    if (reserveTime_ > 0) this->reserveTime = reserveTime_;
    else if (reserveTime_ == 0) this->reserveTime = 30;
    if (reserveTime < 0 || reserveTime > 120) throw InvalidObjectCreation("FuelManagement", "reserveTime");
    //same as taxiFuel
    if (blockFuel_ > 0) this->blockFuel = blockFuel_;
    else if (blockFuel_ == 0) this->blockFuel = 0;
    if (blockFuel < 0) throw InvalidObjectCreation("FuelManagement", "blockFuel");
    //taxiFuel value can be inserted or calculated afterwards
    if (taxiFuel_ > 0) this->taxiFuel = taxiFuel_;
    else if (taxiFuel_ == 0) this->taxiFuel = 0;
    if (taxiFuel < 0 || (taxiFuel > blockFuel && blockFuel > 0)) throw InvalidObjectCreation("FuelManagement", "taxiFuel");
}
FuelManagement::~FuelManagement() = default;
//contingencyFuel = extra fuel needed in case of any unwanted event
void FuelManagement::setContingencyFuel(){this->contingencyFuel = contingencyPct * this->tripFuel;}
//setBlockFuel can be used when the blockFuel parameter isn't mentioned when creating the flight plan
void FuelManagement::setBlockFuel(){this->blockFuel = this->taxiFuel + this->tripFuel + this->contingencyFuel + this->reserveFuel + this->extraFuel;}
//setCalculatedFuel is being used when the blockFuel is mentioned and we need to check if the blockFuel is sufficient for the trip
void FuelManagement::setCalculatedBlockFuel(){this->calculatedBlockFuel = this->taxiFuel + this->tripFuel + this->contingencyFuel + this->reserveFuel + this->extraFuel;}
//when blockFuel is given, that value may be bigger than the necessary fuel to complete the trip -> extraFuel
void FuelManagement::setExtraFuel(){this->extraFuel = this->blockFuel - this->calculatedBlockFuel;}
void FuelManagement::setMinTakeoffFuel(){this->minimumTakeoffFuel = this->tripFuel + this->contingencyFuel + this->reserveFuel;}
void FuelManagement::setTakeoffFuel(){this->takeoffFuel = this->blockFuel - this->taxiFuel;}
//making sure that we have enough fuel to complete the trip
bool FuelManagement::isFuelSufficient() const{return this->calculatedBlockFuel <= this->blockFuel;}
double FuelManagement::getTaxiFuel() const{return this->taxiFuel;}
double FuelManagement::getBlockFuel() const{return this->blockFuel;}
double FuelManagement::getTripFuel() const{return this->tripFuel;}
void FuelManagement::init(const double& climbDuration, const double& cruiseDuration, const double& descentDuration,
                          const std::shared_ptr<Aircraft>& plane)
{
    //TRIP FUEL CALCULATION
    //to take into account the TOW of the aircraft, the ZFW value is being estimated (emptyWeight + payload)
    //to compute the trip fuel, the TOW value is being recalculated until the new trip fuel value is correct
    double payload = plane->calculatePayload();
    double emptyWeight = plane->getEmptyWeight();
    double estimatedTripFuel = plane->calculateTripFuel(climbDuration, cruiseDuration, descentDuration, emptyWeight + payload);
    for (int i = 0; i < 10; i++)
    {
        double currentContingency = estimatedTripFuel * this->contingencyPct;
        double currentTOW = emptyWeight + payload + estimatedTripFuel +
                            this->reserveFuel + currentContingency;
        double newTripFuel = plane->calculateTripFuel(climbDuration, cruiseDuration, descentDuration, currentTOW);
        if (std::abs(newTripFuel - estimatedTripFuel) < 1.0)
        {
            estimatedTripFuel = newTripFuel;
            break;
        }
        estimatedTripFuel = newTripFuel;
    }
    this->tripFuel = estimatedTripFuel;
    //other fuel parameters
    this->setContingencyFuel();
    this->reserveFuel = plane->calculateReserveFuel(reserveTime);
    if (this->taxiFuel== 0) this->taxiFuel = plane->calculateTaxiFuel();
    if (this->blockFuel == 0)
    {
        this->setBlockFuel();
        this->setCalculatedBlockFuel();
        this->setExtraFuel();
    }
    else
    {
        this->setCalculatedBlockFuel();
        if (this->isFuelSufficient() == false)
            throw InvalidFlightPlanParameters("Inserted block fuel is invalid: not enough fuel to complete the trip!");
    }
    this->setExtraFuel();
    this->setMinTakeoffFuel();
    this->setTakeoffFuel();
    if (plane->fuelCapacityExceeded(blockFuel) == true)
        throw InvalidFlightPlanParameters("Block fuel exceeds aircraft's maximum fuel capacity!");
}
std::ostream& operator<<(std::ostream& os, const FuelManagement& flm)
{
    os << "============================\n";
    os << "===     PLANNED FUEL     ===\n";
    os << "============================\n";
    os << "TRIP: " << flm.tripFuel << " KG\n";
    os << "CONT " <<  flm.contingencyPct << " PCT: " << flm.contingencyFuel << " KG\n";
    os << "FINRES: " << flm.reserveFuel << " KG\n";
    os << "============================\n";
    os << "MINIMUM T/OFF FUEL: " << flm.minimumTakeoffFuel << " KG\n";
    os << "============================\n";
    os << "FOB ADD: " << flm.extraFuel << " KG\n";
    os << "============================\n";
    os << "T/OFF FUEL: " << flm.takeoffFuel << " KG\n";
    os << "TAXI: " << flm.taxiFuel << " KG\n";
    os << "============================\n";
    os << "BLOCK FUEL: " << flm.blockFuel << " KG\n\n";
    return os;
}



