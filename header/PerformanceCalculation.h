
#ifndef PERFORMANCECALCULATION_H
#define PERFORMANCECALCULATION_H

#include "FuelManagement.h"
#include "Airport.h"
#include "Aircraft.h"

class PerformanceCalculation
{
private:
    double payload = 0, freight = 0;
    double totalWeight = 0;
    double ZFW = 0, TOW = 0;
    double LDW = 0;
    double takeoffDistance = 0, landingDistance = 0;
    void setZFW(const double& emptyWeight);
    void setTOW(const double& blockFuel, const double& taxiFuel);
    void setLDW(const double& tripFuel);
    void setTotalWeight(const double& blockFuel);
    void setTakeoffDistance(const double& takeoffReferenceDist, const double& maxTakeoffWeight, const Metar& metar);
    void setLandingDistance(const double& takeoffReferenceDist, const double& maxTakeoffWeight,
                            const Metar& metar, const int& runwayDirection, const int& runwayConditon);
public:
    void setPayload(const std::shared_ptr<Aircraft>& plane);
    void setFreight(const std::shared_ptr<Aircraft>& plane);
    [[nodiscard]] double getTakeoffDistance() const;
    [[nodiscard]] double getLandingDistance() const;
    [[nodiscard]] double getFreight() const;
    [[nodiscard]] bool init(const std::shared_ptr<Aircraft>& plane, const FuelManagement& fuelPlanning, const Airport& departure,
                                  const Airport& arrival, const std::string& arrivalRunway);
    friend std::ostream& operator<<(std::ostream& os, const PerformanceCalculation& pfc);
};

#endif //PERFORMANCECALCULATION_H
