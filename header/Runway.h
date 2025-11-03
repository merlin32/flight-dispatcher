#ifndef RUNWAY_H
#define RUNWAY_H

#include <string>
#include <iostream>

enum RwCond {Dry, Wet};

class Runway
{
private:
    std::string runwayID;
    double runwayLength;
    double runwayWidth;
    RwCond runwayCondition;
    bool runwayInUse;
public:
    explicit Runway(std::string runwayID_, const double& runwayLength_, const double& runwayWidth_, RwCond runwayCondition_, const bool& runwayInUse_);
    Runway(const Runway& other);
    Runway& operator=(const Runway& other);
    Runway(Runway&& other) noexcept;
    Runway& operator=(Runway&& other) noexcept;
    ~Runway();
    friend std::ostream& operator<<(std::ostream& os, const Runway& rw);
    [[nodiscard]] double getLength() const;
    [[nodiscard]] double getWidth() const;
    [[nodiscard]] std::string getRunwayID() const;
    [[nodiscard]] int getRwDirection() const;
    [[nodiscard]] int getRwCondition() const;
};
#endif //RUNWAY_H
