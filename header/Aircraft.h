#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include "FuelManagement.h"
#include "PerformanceCalculation.h"

class Aircraft
{
    double range;
    double cruisingSpeed, wingSpan, maxTakeoffWeight;
    double maxPayload, emptyWeight, fuelCapacity;
    double fuelBurnClimb, fuelBurnCruise, fuelBurnDescent;
    int maxCruisingAltitude;
    FuelManagement fuelPlanning;
    PerformanceCalculation perfCalc;
    double fuelBurnIdle, fuelBurnLowAltitude;
    double maxFreight;
    int maxPassengerCount;
    double takeoffReferenceDist;
    int climbRate, descentRate;
    double climbSpeed;
    int minimumFlightDuration;
public:
    explicit Aircraft(double range_,
            double cruisingSpeed_,
            double wingSpan_,
            double maxTakeoffWeight_,
            double maxPayload_,
            double emptyWeight_,
            double fuelCapacity_,
            double fuelBurnClimb_,
            double fuelBurnCruise_,
            double fuelBurnDescent_,
            int maxCruisingAltitude_,
            const FuelManagement& fuelPlanning_,
            const PerformanceCalculation& perfCalc_,
            double fuelBurnIdle_,
            double fuelBurnLowAltitude_,
            double maxFreight_,
            int maxPassengerCount_,
            double takeoffReferenceDist_,
            int climbRate_,
            int descentRate_,
            double climbSpeed_,
            int minimumFlightDuration_);
    Aircraft(const Aircraft& other);
    ~Aircraft();
    [[nodiscard]] int getMaxCruisingAltitude() const;
    [[nodiscard]] int getClimbRate() const;
    [[nodiscard]] int getDescentRate() const;
    [[nodiscard]] double getCruisingSpeed() const;
    [[nodiscard]] double getClimbSpeed() const;
    [[nodiscard]] int getMinimumFlightDuration() const;
    [[nodiscard]] PerformanceCalculation getPerfCalc() const;
    [[nodiscard]] double getRange() const;
    friend std::ostream& operator<<(std::ostream& os, const Aircraft& ac);

};

#endif //AIRCRAFT_H
