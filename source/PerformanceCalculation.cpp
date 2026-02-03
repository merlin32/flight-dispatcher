#include "../header/PerformanceCalculation.h"
#include "../header/JsonUtils.h"
#include <iostream>

#include "../header/Exceptions.h"

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
void PerformanceCalculation::setTakeoffDistance(const double& takeoffReferenceDist, const double& maxTakeoffWeight,
                                                const double& qnhsRatio, const double& temperaturesRatio)
{
    double massesRatio = this->TOW / maxTakeoffWeight;
    double distance = takeoffReferenceDist * massesRatio * qnhsRatio * temperaturesRatio;
    this->takeoffDistance = distance;
}
void PerformanceCalculation::setLandingDistance(const double& takeoffReferenceDist, const double& maxTakeoffWeight,
                            const double& qnhsRatio, const double& temperaturesRatio,
                            const double& windSpeed, const int& runwayFactor)
{
    double massesRatio = this->LDW / maxTakeoffWeight;
    //wind factor calculation
    double windFactor;
    if (windSpeed < 0) windFactor = 1 + WIND_SPEED_PCT * (-windSpeed);
    else windFactor = 1 - WIND_SPEED_PCT * windSpeed;
    double distance = (TAKEOFF_REF_DIST_PCT * takeoffReferenceDist) * massesRatio * qnhsRatio * temperaturesRatio * windFactor * runwayFactor;
    this->landingDistance = distance;
}
double PerformanceCalculation::getTakeoffDistance() const{return this->takeoffDistance;}
double PerformanceCalculation::getLandingDistance() const{return this->landingDistance;}
void PerformanceCalculation::init(const std::shared_ptr<Aircraft>& plane, const FuelManagement& fuelPlanning, const Airport& departure,
                                  const Airport& arrival, const std::string& arrivalRunway)
{
    if (plane->isDataValid() == false)
        throw InvalidFlightPlanParameters("Invalid payload data!");
    if (plane->maxFreightExceeded(freight) == true)
        throw InvalidFlightPlanParameters("Maximum freight value has been exceeded!");
    this->setPayload(plane);
    this->setFreight(plane);
    this->setZFW(plane->getEmptyWeight());
    this->setTOW(fuelPlanning.getBlockFuel(), fuelPlanning.getTaxiFuel());
    this->setLDW(fuelPlanning.getTripFuel());
    this->setTotalWeight(fuelPlanning.getBlockFuel());
    double takeoffReferenceDistance = plane->getTakeoffReferenceDist();
    double maxTakeoffWeight = plane->getMaxTakeoffWeight();
    Metar departMetar = departure.getMetar();
    Metar arrivalMetar = arrival.getMetar();
    Runway arrRw = arrival.getRunway(arrivalRunway);
    this->setTakeoffDistance(takeoffReferenceDistance, maxTakeoffWeight,
                    arrivalMetar.calculateQhnsRatio(),
                             arrivalMetar.calculateTemperaturesRatio());
    this->setLandingDistance(takeoffReferenceDistance, maxTakeoffWeight,
                                      arrivalMetar.calculateQhnsRatio(),
                                      arrivalMetar.calculateTemperaturesRatio(),
                                      arrivalMetar.calculateWindSpeed(arrRw.calculateRwDirection()),
                                      arrRw.runwayFactorDeduction());
    if (plane->maxPayloadExceeded(payload) == true)
        throw InvalidFlightPlanParameters("Maximum payload value has been exceeded!");
    if (plane->maxTakeoffWeightExceeded(TOW) == true)
        throw InvalidFlightPlanParameters("Maximum takeoff weight value has been exceeded!");
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
void PerformanceCalculation::readFromJson(const nlohmann::json& obj)
{
    payload = readAttribute<double>(obj, "payload");
    freight = readAttribute<double>(obj, "freight");
    totalWeight = readAttribute<double>(obj, "totalWeight");
    ZFW = readAttribute<double>(obj, "ZFW");
    TOW = readAttribute<double>(obj, "TOW");
    LDW = readAttribute<double>(obj, "LDW");
    takeoffDistance = readAttribute<double>(obj, "takeoffDistance");
    landingDistance = readAttribute<double>(obj, "landingDistance");
}
void PerformanceCalculation::writeToJson(nlohmann::json& obj) const
{
    writeAttribute<double>(obj, "payload", payload);
    writeAttribute<double>(obj, "freight", freight);
    writeAttribute<double>(obj, "totalWeight", totalWeight);
    writeAttribute<double>(obj, "ZFW", ZFW);
    writeAttribute<double>(obj, "TOW", TOW);
    writeAttribute<double>(obj, "LDW", LDW);
    writeAttribute<double>(obj, "takeoffDistance", takeoffDistance);
    writeAttribute<double>(obj, "landingDistance", landingDistance);
}




