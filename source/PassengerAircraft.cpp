#include "../header/PassengerAircraft.h"
#include "../header/JsonUtils.h"
#include <iostream>

PassengerAircraft::PassengerAircraft(const std::string& category_,
             const std::string& type_,
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
             const int& minimumFlightDuration_,
             const int& maxPassengerCount_ = 0,
             const int& crewCount_ = 2) : Aircraft{category_, type_, range_, cruisingSpeed_,
             wingspan_, maxTakeoffWeight_, maxPayload_, emptyWeight_, fuelCapacity_,
             fuelBurnClimb_, fuelBurnCruise_, fuelBurnDescent_, maxCruisingAltitude_,
             fuelBurnIdle_, fuelBurnLowAltitude_, maxFreight_, takeoffReferenceDist_,
             climbRate_, descentRate_, climbSpeed_, minimumFlightDuration_}, maxPassengerCount{maxPassengerCount_},
             crewCount{crewCount_}{}
std::shared_ptr<Aircraft> PassengerAircraft::clone() const{return std::make_shared<PassengerAircraft>(*this);}
//on average, a person is estimated to weight around 75 kg
double PassengerAircraft::calculatePayload_() const{return 75 * (passengerNumber + crewCount) + freight;}
//on average, a person is estimated to have 10kg of baggage
double PassengerAircraft::calculateFreight_() const
{
    if (freight == 0)
        return 10 * (passengerNumber + crewCount);
    return freight;
}
void PassengerAircraft::readFromJson_(const nlohmann::json& obj)
{
    maxPassengerCount = readAttribute<int>(obj, "maxPassengerCount");
    crewCount = readAttribute<int>(obj, "crewCount");
}

void PassengerAircraft::display(std::ostream &os) const
{
    os << "Maximum passenger capacity: " << maxPassengerCount << '\n';
    os << "Crew count: " << crewCount << '\n';
}
bool PassengerAircraft::isDataValid_() const
{
    //replacement for maxPassengersExceeded() function
    if (passengerNumber > maxPassengerCount)
    {
        std::cerr << "Passengers number has been exceeded!\n";
        return false;
    }
    return true;
}
void PassengerAircraft::aircraftCategoryInit_()
{
    std::cout << "Freight: ";
    std::cin >> freight;
    std::cout << "Passengers: ";
    std::cin >> passengerNumber;
}





