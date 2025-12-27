#include "../header/PerformanceCalculation.h"
#include <iostream>

void PerformanceCalculation::setPayload(const std::shared_ptr<Aircraft>& plane)
{
    this->payload = plane->calculatePayload();
}
void PerformanceCalculation::setFreight(const std::shared_ptr<Aircraft>& plane)
{
    this->freight = plane->calculateFreight();
}
//ZFW = zero fuel weight
void PerformanceCalculation::setZFW(const double& emptyWeight){this->ZFW = emptyWeight + this->payload;}
//TOW = Takeoff weight
void PerformanceCalculation::setTOW(const double& blockFuel, const double& taxiFuel){this->TOW = this->ZFW + blockFuel - taxiFuel;}
//LDW = landing weight
void PerformanceCalculation::setLDW(const double& tripFuel){this->LDW = this->TOW - tripFuel;}
void PerformanceCalculation::setTotalWeight(const double& blockFuel){this->totalWeight = this->ZFW + blockFuel;}
void PerformanceCalculation::setTakeoffDistance(const double& takeoffReferenceDist, const double& maxTakeoffWeight, const Metar& metar)
{
    double massesRatio = (this->TOW / maxTakeoffWeight) * (this->TOW / maxTakeoffWeight);
    double qnhsRatio = metar.calculateQhnsRatio();
    double temperaturesRatio = metar.calculateTemperaturesRatio();
    double distance = takeoffReferenceDist * massesRatio * qnhsRatio * temperaturesRatio;
    this->takeoffDistance = distance;
}
void PerformanceCalculation::setLandingDistance(const double& takeoffReferenceDist, const double& maxTakeoffWeight,
                                                const Metar& metar, const int& runwayDirection, const int& runwayConditon)
{
    double massesRatio = (this->LDW / maxTakeoffWeight) * (this->LDW / maxTakeoffWeight);
    double qnhsRatio = metar.calculateQhnsRatio();
    double temperaturesRatio = metar.calculateTemperaturesRatio();
    //wind factor calculation
    double headWindSpeed = metar.calculateWindSpeed(runwayDirection);
    double windFactor;
    if (headWindSpeed < 0) windFactor = 1 + 0.01 * (-headWindSpeed);
    else windFactor = 1 - 0.01 * headWindSpeed;
    //runwayFactor deduction
    double runwayFactor;
    switch(runwayConditon)
    {
        case 0: runwayFactor = 1; break;
        case 1: runwayFactor = 1.20; break;
        default: runwayFactor = 1; break;
    }
    double distance = takeoffReferenceDist * massesRatio * qnhsRatio * temperaturesRatio * windFactor * runwayFactor;
    this->landingDistance = distance;
}
double PerformanceCalculation::getTakeoffDistance() const{return this->takeoffDistance;}
double PerformanceCalculation::getLandingDistance() const{return this->landingDistance;}
double PerformanceCalculation::getFreight() const{return this->freight;}
bool PerformanceCalculation::init(const std::shared_ptr<Aircraft>& plane, const FuelManagement& fuelPlanning, const Airport& departure,
                                  const Airport& arrival, const std::string& arrivalRunway)
{
    if (plane->isDataValid() == false)
        return false;
    if (plane->maxFreightExceeded(freight) == true)
    {
        std::cerr << "Maximum freight value has been exceeded!\n";
        return false;
    }
    this->setPayload(plane);
    if (this->getFreight() == 0)
        this->setFreight(plane);
    this->setZFW(plane->getEmptyWeight());
    this->setTOW(fuelPlanning.getBlockFuel(), fuelPlanning.getTaxiFuel());
    this->setLDW(fuelPlanning.getTripFuel());
    this->setTotalWeight(fuelPlanning.getBlockFuel());
    double takeoffReferenceDistance = plane->getTakeoffReferenceDist();
    double maxTakeoffWeight = plane->getMaxTakeoffWeight();
    this->setTakeoffDistance(takeoffReferenceDistance, maxTakeoffWeight, departure.getMetar());
    this->setLandingDistance(takeoffReferenceDistance, maxTakeoffWeight,
                                      arrival.getMetar(),
                                      arrival.getRunway(arrivalRunway).getRwDirection(),
                                      arrival.getRunway(arrivalRunway).getRwCondition());
    if (plane->maxPayloadExceeded(payload) == true)
    {
        std::cerr << "Maximum payload value has been exceeded!\n";
        return false;
    }
    if (plane->maxTakeoffWeightExceeded(TOW) == true)
    {
        std::cerr << "Maximum takeoff weight value has been exceeded!\n";
        return false;
    }
    return true;
}
std::ostream& operator<<(std::ostream& os, const PerformanceCalculation& pfc)
{
    os << "=======================================\n";
    os << "===     PERFORMANCE CALCULATION     ===\n";
    os << "=======================================\n";
    os << "PAYLOAD: " << pfc.payload << " KG\n";
    os << "FREIGHT: " << pfc.freight << " KG\n";
    os << "TOTAL WEIGHT: " << pfc.totalWeight << " KG\n";
    os << "ZFW: " << pfc.ZFW << " KG\n";
    os << "TOW: " << pfc.TOW << " KG\n";
    os << "LDW: " << pfc.LDW << " KG\n";
    os << "TAKEOFF DISTANCE: " << pfc.takeoffDistance << " M\n";
    os << "LANDING DISTANCE: " << pfc.landingDistance << " M\n\n";
    return os;
}



