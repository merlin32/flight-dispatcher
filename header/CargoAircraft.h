
#ifndef CARGOAIRCRAFT_H
#define CARGOAIRCRAFT_H

#include "Aircraft.h"
#include <vector>

class CargoAircraft : public Aircraft
{
private:
    int maxContainersNum = 0;
    int crewCount = 1;
    int containersNum = 0;
    double maxContainerWeight = 0;
    std::vector<double> containersWeights;
    [[nodiscard]] double calculatePayload_() const override;
    [[nodiscard]] double calculateFreight_() const override;
    void readFromJson_(const nlohmann::json& obj) override;
    void display(std::ostream &os) const override;
    [[nodiscard]] bool maxContainersNumExceeded() const;
    [[nodiscard]] bool maxContainerWeightExceeded() const;
    [[nodiscard]] bool isDataValid_() const override;
public:
    CargoAircraft() = default;
    explicit CargoAircraft(const std::string& category_,
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
             const int& maxContainersNum_,
             const int& crewCount_,
             const double& maxContainerWeight_);
    [[nodiscard]] std::shared_ptr<Aircraft> clone() const override;
    void setContainersNum(const int& inputContainersNum);
    void setContainersWeights(const std::vector<double>& inputValues);

};
#endif //CARGOAIRCRAFT_H
