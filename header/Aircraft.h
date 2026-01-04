#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include <memory>
#include <vector>
#include <nlohmann/json_fwd.hpp>

class Aircraft
{
private:
    static constexpr double RUNWAY_WIDTH_PCT = 0.6;
    static constexpr int TAXI_TIME_DURATION = 20;
    std::string category;
    std::string type;
    double range;
    double cruisingSpeed, wingspan, maxTakeoffWeight;
    double maxPayload, emptyWeight, fuelCapacity;
    double fuelBurnClimb, fuelBurnCruise, fuelBurnDescent;
    int maxCruisingAltitude;
    double fuelBurnIdle, fuelBurnLowAltitude;
    double maxFreight;
    double takeoffReferenceDist;
    int climbRate, descentRate;
    double climbSpeed;
    int minimumFlightDuration;
    [[nodiscard]] virtual double calculatePayload_() const = 0;
    [[nodiscard]] virtual double calculateFreight_() const = 0;
    virtual void readFromJson_(const nlohmann::json& obj) = 0;
    virtual void display(std::ostream &) const {}
    virtual void aircraftCategoryInit_() = 0;
    [[nodiscard]] virtual bool isDataValid_() const = 0;
    static void attributeValidation(const std::string& value, const std::string& attributeName);
    static void attributeValidation(const double& value, const std::string& attributeName);
    static void attributeValidation(const int& value, const std::string& attributeName);
public:
    Aircraft();
    explicit Aircraft(std::string category_,
             std::string type_,
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
             const int& minimumFlightDuration_);
    virtual ~Aircraft() = default;
    [[nodiscard]] virtual std::shared_ptr<Aircraft> clone() const = 0;
    [[nodiscard]] double calculatePayload() const;
    [[nodiscard]] double calculateFreight() const;
    void aircraftCategoryInit();
    [[nodiscard]] bool isDataValid() const;
    [[nodiscard]] double getEmptyWeight() const;
    [[nodiscard]] double getTakeoffReferenceDist() const;
    [[nodiscard]] double getMaxTakeoffWeight() const;
    friend std::ostream& operator<<(std::ostream& os, const Aircraft& ac);
    //moved these calculations from FuelManagement and Route to eliminate some getters
    [[nodiscard]] double calculateTripFuel(const double& climbDuration, const double& cruiseDuration,
                                            const double& descentDuration, const double& TOW) const;
    [[nodiscard]] double calculateReserveFuel(const int& reserveTime) const;
    [[nodiscard]] double calculateTaxiFuel() const;
    [[nodiscard]] double calculateClimbDuration(const double& delta) const;
    [[nodiscard]] double calculateCruiseDuration(const double& delta) const;
    [[nodiscard]] double calculateDescentDuration(const double& delta) const;
    [[nodiscard]] double distanceWhileClimbing(const double& climbDuration) const;
    [[nodiscard]] double distanceWhileDescending(const double& descentDuration) const;
    [[nodiscard]] double climbSpeedVsRateRatio() const;
    [[nodiscard]] double cruiseSpeedVsDescentRateRatio() const;
    [[nodiscard]] static int calculateDefaultTaxiTime();
    void readFromJson(const nlohmann::json& obj);
    //check functions have been moved from FuelManagement, PerformanceCalculation and Route to get rid of some getters
    [[nodiscard]] bool fuelCapacityExceeded(const double& blockFuel) const;
    [[nodiscard]] bool maxPayloadExceeded(const double& payload) const;
    [[nodiscard]] bool maxFreightExceeded(const double& freight) const;
    [[nodiscard]] bool maxTakeoffWeightExceeded(const double& TOW) const;
    [[nodiscard]] bool maxCruiseAltitudeExceeded(const int& cruiseAltitude) const;
    [[nodiscard]] bool flightTooShort(const double& airTime) const;
    [[nodiscard]] bool aircraftRangeExceeded(const double& routeDistance) const;
    [[nodiscard]] bool categoryMatch(const std::string& currentCategory) const;
    [[nodiscard]] bool aircraftTooWide(const double& runwayWidth) const;
    [[nodiscard]] static bool compareAircraftTypes(const std::shared_ptr<Aircraft>& plane1, const std::shared_ptr<Aircraft>& plane2);
    [[nodiscard]] static bool findAircraft(const std::vector<std::shared_ptr<Aircraft>>& aircraftsList, const std::string& inputType,
                                            std::shared_ptr<Aircraft>& plane);
    void displayAircraftType();
protected:
    Aircraft(const Aircraft& other) = default;
    Aircraft &operator=(const Aircraft& other) = default;

};

#endif //AIRCRAFT_H
