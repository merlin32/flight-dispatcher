
#ifndef FUELMANAGEMENT_H
#define FUELMANAGEMENT_H

#include <iostream>

class FuelManagement
{
private:
    //not implemented yet: alternateFuel
    double tripFuel = 0;
    double contingencyPct;
    double contingencyFuel = 0;
    int reserveTime;
    double reserveFuel = 0;
    double taxiFuel = 0;
    double blockFuel = 0;
    double calculatedBlockFuel = 0;
    double extraFuel = 0;
    double minimumTakeoffFuel = 0;
    double takeoffFuel = 0;
public:
    explicit FuelManagement(const double& contingencyPct_, const int& reserveTime_, const double& taxiFuel_, const double& blockFuel_);
    ~FuelManagement();
    void setTripFuel(const double& climbDuration, const double& cruiseDuration, const double& descentDuration,
                 const double& fuelBurnClimb, const double& fuelBurnCruise, const double& fuelBurnDescent);
    void setContingencyFuel();
    void setReserveFuel(const double& fuelBurnLowAltitude);
    void setTaxiFuel(const double& fuelBurnIdle);
    void setBlockFuel();
    void setCalculatedBlockFuel();
    void setExtraFuel();
    void setMinTakeoffFuel();
    void setTakeoffFuel();
    [[nodiscard]] bool isFuelSufficient() const;
    [[nodiscard]] bool fuelCapacityExceeded(const double& fuelCapacity) const;
    [[nodiscard]] double getTaxiFuel() const;
    [[nodiscard]] double getBlockFuel() const;
    [[nodiscard]] double getTripFuel() const;
    friend std::ostream& operator<<(std::ostream& os, const FuelManagement& flm);
};

#endif //FUELMANAGEMENT_H
