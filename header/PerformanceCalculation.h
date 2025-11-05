
#ifndef PERFORMANCECALCULATION_H
#define PERFORMANCECALCULATION_H

#include "Aircraft.h"
#include "FuelManagement.h"
#include "Airport.h"

class PerformanceCalculation
{
private:
    double payload = 0, freight = 0;
    int passengerNumber;
    double totalWeight = 0;
    double ZFW = 0, TOW = 0;
    double LDW = 0;
    double takeoffDistance = 0, landingDistance = 0;
public:
    explicit PerformanceCalculation(const double& freight_, const int& passengerNumber_);
    ~PerformanceCalculation();
private:
    void setPayload();
    void setFreight();
    void setZFW(const double& emptyWeight);
    void setTOW(const double& blockFuel, const double& taxiFuel);
    void setLDW(const double& tripFuel);
    void setTotalWeight(const double& blockFuel);
    void setTakeoffDistance(const double& takeoffReferenceDist, const double& maxTakeoffWeight,
                            const unsigned short int& qnh, const unsigned short int& temperature);
    void setLandingDistance(const double& takeoffReferenceDist, const double& maxTakeoffWeight,
                         const unsigned short int& qnh, const unsigned short int& temperature, const unsigned short int& windSpeed,
                         const unsigned short int& windDirection, const int& runwayDirection, const int& runwayConditon);
    [[nodiscard]] bool maxPayloadExceeded(const double& maxPayload) const;
    [[nodiscard]] bool maxPassengersExceeded(const int& maxPassengerNumber) const;
    [[nodiscard]] bool maxFreightExceeded(const double& maxFreight) const;
    [[nodiscard]] bool maxTakeoffWeightExceeded(const double& maxTakeoffWeight) const;
public:
    [[nodiscard]] double getTakeoffDistance() const;
    [[nodiscard]] double getLandingDistance() const;
    [[nodiscard]] double getFreight() const;
    [[nodiscard]] bool init(const Aircraft& plane, const FuelManagement& fuelPlanning, const Airport& departure,
                                  const Airport& arrival, const std::string& arrivalRunway);
    friend std::ostream& operator<<(std::ostream& os, const PerformanceCalculation& pfc);
};

#endif //PERFORMANCECALCULATION_H
