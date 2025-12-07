#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include <nlohmann/json.hpp>

class Aircraft
{
private:
    std::string type;
    double range;
    double cruisingSpeed, wingSpan, maxTakeoffWeight;
    double maxPayload, emptyWeight, fuelCapacity;
    double fuelBurnClimb, fuelBurnCruise, fuelBurnDescent;
    int maxCruisingAltitude;
    double fuelBurnIdle, fuelBurnLowAltitude;
    double maxFreight;
    double takeoffReferenceDist;
    int climbRate, descentRate;
    double climbSpeed;
    int minimumFlightDuration;
    virtual double calculatePayload_() const = 0;
    virtual double calculateFreight_() const = 0;
    virtual void display(std::ostream &) const {}
public:
    Aircraft();
    explicit Aircraft(std::string type_,
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
             const int& minimumFlightDuration_);
    virtual ~Aircraft() = default;
    virtual std::shared_ptr<Aircraft> clone() const = 0;
    [[nodiscard]] double calculatePayload() const;
    [[nodiscard]] double calculateFreight() const;
    [[nodiscard]] int getMaxCruisingAltitude() const;
    [[nodiscard]] int getClimbRate() const;
    [[nodiscard]] int getDescentRate() const;
    [[nodiscard]] double getCruisingSpeed() const;
    [[nodiscard]] double getClimbSpeed() const;
    [[nodiscard]] int getMinimumFlightDuration() const;
    [[nodiscard]] double getRange() const;
    [[nodiscard]] std::string getType() const;
    [[nodiscard]] double getEmptyWeight() const;
    [[nodiscard]] double getTakeoffReferenceDist() const;
    [[nodiscard]] double getMaxTakeoffWeight() const;
    friend std::ostream& operator<<(std::ostream& os, const Aircraft& ac);
    //moved these calculations from FuelManagement to eliminate some getters
    [[nodiscard]] double calculateTripFuel(const double& climbDuration, const double& cruiseDuration, const double& descentDuration) const;
    [[nodiscard]] double calculateReserveFuel(const int& reserveTime) const;
    [[nodiscard]] double calculateTaxiFuel() const;
    //check functions have been moved from FuelManagement and PerformanceCalculation to get rid of some getters
    [[nodiscard]] bool fuelCapacityExceeded(const double& blockFuel) const;
    [[nodiscard]] bool maxPayloadExceeded(const double& payload) const;
    [[nodiscard]] bool maxFreightExceeded(const double& freight) const;
    [[nodiscard]] bool maxTakeoffWeightExceeded(const double& TOW) const;
protected:
    Aircraft(const Aircraft& other) = default;
    Aircraft &operator=(const Aircraft& other) = default;


};

#endif //AIRCRAFT_H
