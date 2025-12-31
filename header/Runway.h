#ifndef RUNWAY_H
#define RUNWAY_H

#include <string>

class Runway
{
private:
    static constexpr double TAKEOFF_SAFETY_FACTOR = 1.15;
    static constexpr double LANDING_SAFETY_FACTOR = 1.60;
    std::string runwayID;
    double runwayLength;
    double runwayWidth;
    int runwayCondition;
    bool runwayInUse;
public:
    explicit Runway(std::string runwayID_, const double& runwayLength_, const double& runwayWidth_, int runwayCondition_, const bool& runwayInUse_);
    Runway(const Runway& other);
    Runway& operator=(const Runway& other);
    Runway(Runway&& other) noexcept;
    Runway& operator=(Runway&& other) noexcept;
    ~Runway();
    friend std::ostream& operator<<(std::ostream& os, const Runway& rw);
    [[nodiscard]] double getWidth() const;
    [[nodiscard]] bool getRwStatus() const;
    [[nodiscard]] int calculateRwDirection() const;
    [[nodiscard]] double runwayFactorDeduction() const;
    [[nodiscard]] bool runwayCodeMatch(const std::string& testValue) const;
    [[nodiscard]] bool runwayTooShortTakeoff(const double& takeoffDistance) const;
    [[nodiscard]] bool runwayTooShortLanding(const double& landingDistance) const;
};
#endif //RUNWAY_H
