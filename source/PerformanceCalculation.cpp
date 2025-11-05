#include "../header/PerformanceCalculation.h"
#include <cmath>
#include <iostream>

PerformanceCalculation::PerformanceCalculation(const double& freight_, const int& passengerNumber_): passengerNumber{passengerNumber_}
{
    //the user may want to insert only the passengerNumber value
    if (freight_ != 0) this->freight = freight_;
    else this->freight = 0;
}
PerformanceCalculation::~PerformanceCalculation() = default;
//on average, a passenger is estimated to weight around 75 kg
void PerformanceCalculation::setPayload(){this->payload = 75 * passengerNumber + this->freight;}
//on average, a passenger is estimated to have 10kg of baggage
void PerformanceCalculation::setFreight(){this->freight = 10 * passengerNumber;}
//ZFW = zero fuel weight
void PerformanceCalculation::setZFW(const double& emptyWeight){this->ZFW = emptyWeight + this->payload;}
//TOW = Takeoff weight
void PerformanceCalculation::setTOW(const double& blockFuel, const double& taxiFuel){this->TOW = this->ZFW + blockFuel - taxiFuel;}
//LDW = landing weight
void PerformanceCalculation::setLDW(const double& tripFuel){this->LDW = this->TOW - tripFuel;}
void PerformanceCalculation::setTotalWeight(const double& blockFuel){this->totalWeight = this->ZFW + blockFuel;}
void PerformanceCalculation::setTakeoffDistance(const double& takeoffReferenceDist, const double& maxTakeoffWeight,
                        const unsigned short int& qnh, const unsigned short int& temperature)
{
    double massesRatio = (this->TOW / maxTakeoffWeight) * (this->TOW / maxTakeoffWeight);
    double qnhsRatio = (double) 1013 / qnh; //1013 represents the standard air pressure
    double temperaturesRatio = (temperature + 273.15) / 288.15; //288.15 represents the standard air temperature in Kelvins
    double distance = takeoffReferenceDist * massesRatio * qnhsRatio * temperaturesRatio;
    this->takeoffDistance = distance;
}
void PerformanceCalculation::setLandingDistance(const double& takeoffReferenceDist, const double& maxTakeoffWeight,
                        const unsigned short int& qnh, const unsigned short int& temperature, const unsigned short int& windSpeed,
                        const unsigned short int& windDirection, const int& runwayDirection, const int& runwayConditon)
{
    double massesRatio = (this->LDW / maxTakeoffWeight) * (this->LDW / maxTakeoffWeight);
    double qnhsRatio = (double) 1013 / qnh;
    double temperaturesRatio = (temperature + 273.15) / 288.15;
    //wind factor calculation
    double headWindSpeed = windSpeed * cos(windDirection - runwayDirection);
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
bool PerformanceCalculation::maxPayloadExceeded(const double& maxPayload) const {return this->payload > maxPayload;}
bool PerformanceCalculation::maxPassengersExceeded(const int& maxPassengerNumber) const {return this->passengerNumber > maxPassengerNumber;}
bool PerformanceCalculation::maxFreightExceeded(const double& maxFreight) const {return this->freight > maxFreight;}
bool PerformanceCalculation::maxTakeoffWeightExceeded(const double& maxTakeoffWeight) const{return this->TOW > maxTakeoffWeight;}
double PerformanceCalculation::getTakeoffDistance() const{return this->takeoffDistance;}
double PerformanceCalculation::getLandingDistance() const{return this->landingDistance;}
double PerformanceCalculation::getFreight() const{return this->freight;}
bool PerformanceCalculation::init(const Aircraft& plane, const FuelManagement& fuelPlanning, const Airport& departure,
                                  const Airport& arrival, const std::string& arrivalRunway)
{
    if (this->maxPassengersExceeded(plane.getMaxPassengerCount()))
    {
        std::cerr << "Passengers number has been exceeded!\n";
        return false;
    }
    if (this->maxFreightExceeded(plane.getMaxFreight()) == true)
    {
        std::cerr << "Maximum freight value has been exceeded!\n";
        return false;
    }
    this->setPayload();
    if (this->getFreight() == 0)
        this->setFreight();
    this->setZFW(plane.getEmptyWeight());
    this->setTOW(fuelPlanning.getBlockFuel(), fuelPlanning.getTaxiFuel());
    this->setLDW(fuelPlanning.getTripFuel());
    this->setTotalWeight(fuelPlanning.getBlockFuel());
    this->setTakeoffDistance(plane.getTakeoffReferenceDist(),
                                      plane.getMaxTakeoffWeight(),
                                      departure.getWeather().getMetar().getQnh(),
                                      departure.getWeather().getMetar().getTemperature());
    this->setLandingDistance(plane.getTakeoffReferenceDist(), plane.getMaxTakeoffWeight(),
                                      arrival.getWeather().getMetar().getQnh(),
                                      arrival.getWeather().getMetar().getTemperature(),
                                      arrival.getWeather().getMetar().getWindSpeed(),
                                      arrival.getWeather().getMetar().getWindDirection(),
                                      arrival.getRunway(arrivalRunway).getRwDirection(),
                                      arrival.getRunway(arrivalRunway).getRwCondition());
    if (this->maxPayloadExceeded(plane.getMaxPayload()) == true)
    {
        std::cerr << "Maximum payload value has been exceeded!\n";
        return false;
    }
    if (this->maxTakeoffWeightExceeded(plane.getMaxTakeoffWeight()) == true)
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
    os << "PASSENGER NUMBER: " << pfc.passengerNumber << '\n';
    os << "TOTAL WEIGHT: " << pfc.totalWeight << " KG\n";
    os << "ZFW: " << pfc.ZFW << " KG\n";
    os << "TOW: " << pfc.TOW << " KG\n";
    os << "LDW: " << pfc.LDW << " KG\n";
    os << "TAKEOFF DISTANCE: " << pfc.takeoffDistance << " M\n";
    os << "LANDING DISTANCE: " << pfc.landingDistance << " M\n\n";
    return os;
}



