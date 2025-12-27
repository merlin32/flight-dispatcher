#include "../header/GeneralAviationAircraft.h"
#include <iostream>
#include <nlohmann/json.hpp>

GeneralAviationAircraft::GeneralAviationAircraft(const std::string& category_,
             const std::string& type_,
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
             const int& maxPilotCount_,
             const int& maxPassengersNumber_) : Aircraft{category_, type_, range_, cruisingSpeed_,
             wingSpan_, maxTakeoffWeight_, maxPayload_, emptyWeight_, fuelCapacity_,
             fuelBurnClimb_, fuelBurnCruise_, fuelBurnDescent_, maxCruisingAltitude_,
             fuelBurnIdle_, fuelBurnLowAltitude_, maxFreight_, takeoffReferenceDist_,
             climbRate_, descentRate_, climbSpeed_, minimumFlightDuration_},
             maxPilotCount{maxPilotCount_}, maxPassengersNumber{maxPassengersNumber_}{}
std::shared_ptr<Aircraft> GeneralAviationAircraft::clone() const{return std::make_shared<GeneralAviationAircraft>(*this);}
double GeneralAviationAircraft::calculatePayload_() const
{
    return 80 * (pilotsCount + passengersNumber) + baggageWeight;
}
double GeneralAviationAircraft::calculateFreight_() const{return baggageWeight;}
void GeneralAviationAircraft::readFromJson_(const nlohmann::json& obj)
{
    maxPilotCount = obj["maxPilotCount"];
    maxPassengersNumber = obj["maxPassengersNumber"];
}

void GeneralAviationAircraft::display(std::ostream &os) const
{
    os << "Maximum number of pilots: " << maxPilotCount << '\n';
    os << "Maximum number of passengers: " << maxPassengersNumber << '\n';
    os << "Number of pilots in charge: " << pilotsCount << '\n';
    os << "Number of boarded passengers: " << passengersNumber << '\n';
}
bool GeneralAviationAircraft::maxPilotCountExceeded() const{return pilotsCount > maxPilotCount;}
bool GeneralAviationAircraft::maxPassengersNumberExceeded() const{return passengersNumber > maxPassengersNumber;}
void GeneralAviationAircraft::setPilotsCount(const int& inputValue) {this->pilotsCount = inputValue;}
void GeneralAviationAircraft::setPassengersNumber(const int& inputValue){this->passengersNumber = inputValue;}
void GeneralAviationAircraft::setBaggageWeight(const double& inputValue){this->baggageWeight = inputValue;}
bool GeneralAviationAircraft::isDataValid_() const
{
    if (maxPilotCountExceeded() == true)
    {
        std::cerr << "Maximum number of pilots exceeded!\n";
        return false;
    }
    if (maxPassengersNumberExceeded() == true)
    {
        std::cerr << "Passengers number has been exceeded!\n";
        return false;
    }
    return true;
}




