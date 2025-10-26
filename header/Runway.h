#ifndef RUNWAY_H
#define RUNWAY_H

#include <string>
#include <iostream>

enum RwCond {Dry, Wet};

class Runway
{
private:
    std::string runwayID;
    int runwayLength;
    RwCond runwayCondition;
    bool runwayInUse = false;
public:
    explicit Runway(std::string runwayID_, const int& runwayLength_, RwCond runwayCondition_, const bool& runwayInUse_);
    Runway(const Runway& other);
    ~Runway();
    friend std::ostream& operator<<(std::ostream& os, const Runway& rw);
    [[nodiscard]] int getLength() const;
};
#endif //RUNWAY_H
