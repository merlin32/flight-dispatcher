#ifndef PASSENGERAIRCRAFT_H
#define PASSENGERAIRCRAFT_H

#include "Aircraft.h"

class PassengerAircraft : public Aircraft
{
private:
    int maxPassengerCount;
    int crewCount = 0;
    int freight = 0;
    int passengerNumber = 0;
    [[nodiscard]] double calculatePayload_() const override;
    [[nodiscard]] double calculateFreight_() const override;
    void readFromJson_(const nlohmann::json& obj) override;
    void display(std::ostream &os) const override;
    [[nodiscard]] bool isDataValid_() const override;
public:
    PassengerAircraft() = default;
    explicit PassengerAircraft(const std::string& category_,
             const std::string& type_,
             const double& range_,
             const double& cruisingSpeed_,
             const double& wingspan_,
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
             const int& maxPassengerCount_,
             const int& crewCount_);
    [[nodiscard]] std::shared_ptr<Aircraft> clone() const override;
    void setFreight(const int& inputFreight);
    void setPassengerNumber(const int& inputPassengerNumber);
};
#endif //PASSENGERAIRCRAFT_H
