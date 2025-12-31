#include "../header/CargoAircraft.h"
#include "../header/JsonUtils.h"
#include <iostream>
#include <nlohmann/json.hpp>

CargoAircraft::CargoAircraft(const std::string& category_,
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
             const int& maxContainersNum_ = 0,
             const int& crewCount_ = 2,
             const double& maxContainerWeight_ = 0) : Aircraft{category_, type_, range_, cruisingSpeed_,
             wingspan_, maxTakeoffWeight_, maxPayload_, emptyWeight_, fuelCapacity_,
             fuelBurnClimb_, fuelBurnCruise_, fuelBurnDescent_, maxCruisingAltitude_,
             fuelBurnIdle_, fuelBurnLowAltitude_, maxFreight_, takeoffReferenceDist_,
             climbRate_, descentRate_, climbSpeed_, minimumFlightDuration_}, maxContainersNum{maxContainersNum_},
             crewCount{crewCount_}, maxContainerWeight{maxContainerWeight_}{}
std::shared_ptr<Aircraft> CargoAircraft::clone() const{return std::make_shared<CargoAircraft>(*this);}
double CargoAircraft::calculatePayload_() const
{
    return 75 * crewCount + calculateFreight_();
}
double CargoAircraft::calculateFreight_() const
{
    double totalContainersWeight = 0;
    for (int i = 0; i < containersNum; i++)
        totalContainersWeight += containersWeights[i];
    return totalContainersWeight;
}
void CargoAircraft::readFromJson_(const nlohmann::json& obj)
{
    maxContainersNum = readAttribute<int>(obj, "maxContainersNum");
    crewCount = readAttribute<int>(obj, "crewCount");
    maxContainerWeight = readAttribute<double>(obj, "maxContainerWeight");
}

void CargoAircraft::display(std::ostream &os) const
{
    os << "Maximum containers available to load: " << maxContainersNum << '\n';
    os << "Crew count: " << crewCount << '\n';
    os << "Containers loaded: " << containersNum << '\n';
    os << "Maximum allowed container's weight: " << maxContainerWeight << '\n';
    os << "Each container's weight: \n";
    for (int i = 0; i < containersNum; i++)
        os << "\tContainer " << i << ": " << containersWeights[i] << '\n';
}
bool CargoAircraft::maxContainersNumExceeded() const {return containersNum > maxContainersNum;}
bool CargoAircraft::maxContainerWeightExceeded() const
{
    for (const auto&i : containersWeights)
        if (i > maxContainerWeight)
            return true;
    return false;
}
void CargoAircraft::setContainersNum(const int& inputContainersNum){this->containersNum = inputContainersNum;}
void CargoAircraft::setContainersWeights(const std::vector<double>& inputValues){this->containersWeights = inputValues;}
bool CargoAircraft::isDataValid_() const
{
    if (maxContainersNumExceeded() == true)
    {
        std::cerr << "Number of maximum container slots exceeded!\n";
        return false;
    }
    if (maxContainerWeightExceeded() == true)
    {
        std::cerr << "Container maximum weight has been exceeded!\n";
        return false;
    }
    return true;
}






