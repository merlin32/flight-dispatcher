#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include <iostream>

class Aircraft
{
    double range;
    double cruisingSpeed, wingSpan, maxTakeoffWeight;
    double maxPayload, emptyWeight, fuelCapacity;
    double fuelConsumptionClimb, fuelConsumptionCruise, fuelConsumptionDescent;
    double takeoffDistance, landingDistance;
    int cruisingAltitude, climbRate, descentRate;
    std::string registrationNumber;
public:
    explicit Aircraft(const double& range_, const double& cruisingSpeed_, const double& wingSpan_, const double& maxTakeoffWeight_,
            const double& maxPayload_, const double& emptyWeight_, const double& fuelCapacity_,
            const double& fuelConsumptionClimb_, const double& fuelConsumptionCruise_, const double& fuelConsumptionDescent_,
            const double& takeoffDistance_, const double& landingDistance_,
            const int& cruisingAltitude_, const int& climbRate_, const int& descentRate_,
            std::string registrationNumber_);
    Aircraft(const Aircraft& other);
    ~Aircraft();
    friend std::ostream& operator<<(std::ostream& os, const Aircraft& ac);
    //[[nodiscard]] double fuelCalculation(const double& taxiFuel, const double& blockFuel);
};

#endif //AIRCRAFT_H
