#include "../header/Aircraft.h"

Aircraft::Aircraft(const double& range_, const double& cruisingSpeed_, const double& wingSpan_, const double& maxTakeoffWeight_,
            const double& maxPayload_, const double& emptyWeight_, const double& fuelCapacity_,
            const double& fuelConsumptionClimb_, const double& fuelConsumptionCruise_, const double& fuelConsumptionDescent_,
            const double& takeoffDistance_, const double& landingDistance_,
            const int& cruisingAltitude_, const int& climbRate_, const int& descentRate_,
            std::string registrationNumber_):
                        range{range_}, cruisingSpeed{cruisingSpeed_}, wingSpan{wingSpan_}, maxTakeoffWeight{maxTakeoffWeight_},
                        maxPayload{maxPayload_}, emptyWeight{emptyWeight_}, fuelCapacity{fuelCapacity_},
                        fuelConsumptionClimb{fuelConsumptionClimb_}, fuelConsumptionCruise{fuelConsumptionCruise_},
                        fuelConsumptionDescent{fuelConsumptionDescent_}, takeoffDistance{takeoffDistance_},
                        landingDistance{landingDistance_}, cruisingAltitude{cruisingAltitude_},
                        climbRate{climbRate_}, descentRate{descentRate_},
                        registrationNumber{std::move(registrationNumber_)}{}
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
    os << "Fuel capacity: " << ac.fuelCapacity << '\n';
    os << "Fuel consumption (Climb): " << ac.fuelConsumptionClimb << '\n';
    os << "Fuel consumption (Cruise): " << ac.fuelConsumptionCruise << '\n';
    os << "Fuel consumption (Descent): " << ac.fuelConsumptionDescent << '\n';
    os << "Takeoff distance: " << ac.takeoffDistance << '\n';
    os << "Landing distance: " << ac.landingDistance << '\n';
    os << "Cruising Altitude: " << ac.cruisingAltitude << '\n';
    os << "Climb rate: " << ac.climbRate << '\n';
    os << "Descent rate: " << ac.descentRate << '\n';
    os << "Registration number: " << ac.registrationNumber << '\n';
    return os;
 }
