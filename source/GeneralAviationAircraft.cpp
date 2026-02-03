#include "../header/GeneralAviationAircraft.h"
#include "../header/JsonUtils.h"
#include "../header/VectorUtils.h"
#include <iostream>
#include <cmath>


GeneralAviationAircraft::GeneralAviationAircraft(const std::string& category_,
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
                                                 const int& maxPilotCount_ = 1,
                                                 const int& maxPassengersNumber_ = 0) : Aircraft{category_, type_, range_, cruisingSpeed_,
                                                                                            wingspan_, maxTakeoffWeight_, maxPayload_, emptyWeight_, fuelCapacity_,
                                                                                            fuelBurnClimb_, fuelBurnCruise_, fuelBurnDescent_, maxCruisingAltitude_,
                                                                                            fuelBurnIdle_, fuelBurnLowAltitude_, maxFreight_, takeoffReferenceDist_,
                                                                                            climbRate_, descentRate_, climbSpeed_, minimumFlightDuration_},
                                                                                        maxPilotCount{maxPilotCount_}, maxPassengersNumber{maxPassengersNumber_}{}
std::shared_ptr<Aircraft> GeneralAviationAircraft::clone() const{return std::make_unique<GeneralAviationAircraft>(*this);}
double GeneralAviationAircraft::calculatePayload_() const
{
    return 75 * (pilotsCount + passengersNumber) + baggageWeight;
}
double GeneralAviationAircraft::calculateFreight_() const{return baggageWeight;}
void GeneralAviationAircraft::readFromJson_(const nlohmann::json& obj)
{
    maxPilotCount = readAttribute<int>(obj, "maxPilotCount");
    maxPassengersNumber = readAttribute<int>(obj, "maxPassengersNumber");
}

void GeneralAviationAircraft::display(std::ostream &os) const
{
    os << "Maximum number of pilots: " << maxPilotCount << '\n';
    os << "Maximum number of passengers: " << maxPassengersNumber << "\n\n";
    os << "Number of pilots in charge: " << pilotsCount << '\n';
    os << "Number of boarded passengers: " << passengersNumber << '\n';
    os << "Total baggage weight: " << baggageWeight << " KG\n";
}
bool GeneralAviationAircraft::maxPilotCountExceeded() const{return pilotsCount > maxPilotCount;}
bool GeneralAviationAircraft::maxPassengersNumberExceeded() const{return passengersNumber > maxPassengersNumber;}
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
void GeneralAviationAircraft::aircraftCategoryInit_()
{
    char buf[8];
    snprintf(buf, sizeof(buf), "%.2f", std::trunc(maxFreight * 100.0) / 100.0);
    if (maxPilotCount > 1)
        validInputItem<int>("Number of pilots (MAX: " + std::to_string(maxPilotCount) + "): ", pilotsCount);
    validInputItem<int>("Passengers (MAX: " + std::to_string(maxPassengersNumber) + "): ", passengersNumber);
    validInputItem<double>("Baggage quantity (MAX: " + std::string(buf) + " KG): ", baggageWeight);
}
void GeneralAviationAircraft::readParamsFromJson_(const nlohmann::json& obj)
{
    pilotsCount = readAttribute<int>(obj, "pilotsCount");
    passengersNumber = readAttribute<int>(obj, "passengersNumber");
    baggageWeight = readAttribute<double>(obj, "baggageWeight");
}
void GeneralAviationAircraft::writeParamsToJson_(nlohmann::json& obj)
{
    writeAttribute<int>(obj, "pilotsCount", pilotsCount);
    writeAttribute<int>(obj, "passengersNumber", passengersNumber);
    writeAttribute<double>(obj, "baggageWeight", baggageWeight);
}





