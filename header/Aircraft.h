#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include "FuelManagement.h"

class Aircraft
{
    double range;
    double cruisingSpeed, wingSpan, maxTakeoffWeight;
    double maxPayload, emptyWeight, fuelCapacity;
    double fuelBurnClimb, fuelBurnCruise, fuelBurnDescent;
    double takeoffDistance, landingDistance;
    int maxCruisingAltitude;
    std::string registrationNumber;
    FuelManagement fuelPlanning; //not in constructor yet
public:
    explicit Aircraft(const double& range_, const double& cruisingSpeed_, const double& wingSpan_, const double& maxTakeoffWeight_,
            const double& maxPayload_, const double& emptyWeight_, const double& fuelCapacity_,
            const double& fuelBurnClimb_, const double& fuelBurnCruise_, const double& fuelBurnDescent_,
            const double& takeoffDistance_, const double& landingDistance_,
            const int& maxCruisingAltitude_,
            std::string registrationNumber_);
    Aircraft(const Aircraft& other);
    ~Aircraft();
    friend std::ostream& operator<<(std::ostream& os, const Aircraft& ac);
};

#endif //AIRCRAFT_H
