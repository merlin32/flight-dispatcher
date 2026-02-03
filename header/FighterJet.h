
#ifndef FIGHTERJET_H
#define FIGHTERJET_H

#include "Aircraft.h"

class FighterJet : public Aircraft
{
private:
    static constexpr double PILOT_WEIGHT = 90;
    int numberOfPilots = 1;
    int maxNumberOfPilots = 2;
    int missileCount = 0;
    int maxMissileCount = 4;
    double weightPerMissile = 0;
    double maxMissileWeight = 150.0;
    double cannonAmmoWeight = 0;
    double maxCannonAmmoWeight = 30;
    [[nodiscard]] double calculatePayload_() const override;
    [[nodiscard]] double calculateFreight_() const override;
    void readFromJson_(const nlohmann::json& obj) override;
    void display(std::ostream &os) const override;
    void aircraftCategoryInit_() override;
    void readParamsFromJson_(const nlohmann::json& obj) override;
    void writeParamsToJson_(nlohmann::json& obj) override;
    [[nodiscard]] bool isDataValid_() const override;
    [[nodiscard]] bool maxPilotCountExceeded() const;
    [[nodiscard]] bool maxMissileCountExceeded() const;
    [[nodiscard]] bool maxMissileWeightExceeded() const;
    [[nodiscard]] bool maxCannonAmmoWeightExceeded() const;
public:
    FighterJet() = default;
    explicit FighterJet(const std::string& category_,
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
             const int& maxNumberOfPilots_,
             const int& maxMissileCount_,
             const double& maxMissileWeight_,
             const double& maxCannonAmmoWeight_);
    [[nodiscard]] std::shared_ptr<Aircraft> clone() const override;
};

#endif //FIGHTERJET_H
