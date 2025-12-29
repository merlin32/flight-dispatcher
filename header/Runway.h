#ifndef RUNWAY_H
#define RUNWAY_H

#include <string>
#include <iostream>

class Runway
{
private:
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
    [[nodiscard]] double getLength() const;
    [[nodiscard]] std::string getRunwayID() const;
    [[nodiscard]] int getRwDirection() const;
    [[nodiscard]] int getRwCondition() const;
    [[nodiscard]] bool getRwStatus() const;
};
#endif //RUNWAY_H
