#include "../header/Aircraft.h"

Aircraft::Aircraft(const double& range_, const double& cruisingSpeed_, const double& wingSpan_, const double& maxTakeoffWeight_,
            const double& maxPayload_, const double& emptyWeight_, const double& fuelCapacity_,
            const double& fuelBurnClimb_, const double& fuelBurnCruise_, const double& fuelBurnDescent_,
            const double& takeoffDistance_, const double& landingDistance_,
            const int& maxCruisingAltitude_, std::string registrationNumber_):
                        range{range_}, cruisingSpeed{cruisingSpeed_}, wingSpan{wingSpan_}, maxTakeoffWeight{maxTakeoffWeight_},
                        maxPayload{maxPayload_}, emptyWeight{emptyWeight_}, fuelCapacity{fuelCapacity_},
                        fuelBurnClimb{fuelBurnClimb_}, fuelBurnCruise{fuelBurnCruise_},
                        fuelBurnDescent{fuelBurnDescent_}, takeoffDistance{takeoffDistance_},
                        landingDistance{landingDistance_}, maxCruisingAltitude{maxCruisingAltitude_},
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
    os << "Fuel consumption (Climb): " << ac.fuelBurnClimb << '\n';
    os << "Fuel consumption (Cruise): " << ac.fuelBurnCruise << '\n';
    os << "Fuel consumption (Descent): " << ac.fuelBurnDescent << '\n';
    os << "Takeoff distance: " << ac.takeoffDistance << '\n';
    os << "Landing distance: " << ac.landingDistance << '\n';
    os << "Maximum Cruising Altitude: " << ac.maxCruisingAltitude << '\n';
    os << "Registration number: " << ac.registrationNumber << '\n';
    return os;
 }
