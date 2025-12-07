
#ifndef GENERALAVIATIONAIRCRAFT_H
#define GENERALAVIATIONAIRCRAFT_H

#include "Aircraft.h"

class GeneralAviationAircraft : public Aircraft
{
private:
    int maxPilotCount;
    int maxPassengersNumber;
    int pilotsCount = 0;
    int passengersNumber = 0;
    double baggageWeight = 0;
    double calculatePayload_() const override;
    double calculateFreight_() const override;
    void display(std::ostream &os) const override;
public:
    explicit GeneralAviationAircraft(const std::string& type_,
             const double& range_,
             const double& cruisingSpeed_,
             const double& wingSpan_,
             const double& maxTakeoffWeight_,
             const double& maxPayload_,
             const double& emptyWeight_,
             const double& fuelCapacity_,
             const double& fuelBurnClimb_,
             const double& fuelBurnCruise_,
             const double& fuelBurnDescent_,
             const int& maxCruisingAltitude_,
             const double& fuelBurnIdle_,
             const double& fuelBurnLowAltitude_,
             const double& maxFreight_,
             const double& takeoffReferenceDist_,
             const int& climbRate_,
             const int& descentRate_,
             const double& climbSpeed_,
             const int& minimumFlightDuration_,
             const int& maxPilotCount_,
             const int& maxPassengersNumber_);
    [[nodiscard]] std::shared_ptr<Aircraft> clone() const override;
    [[nodiscard]] bool maxPilotCountExceeded() const;
    [[nodiscard]] bool maxPassengersNumberExceeded() const;
    void setPilotsCount(const int& inputValue);
    void setPassengersNumber(const int& inputValue);
    void setBaggageWeight(const double& inputValue);
};

#endif //GENERALAVIATIONAIRCRAFT_H
