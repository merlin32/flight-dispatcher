#include "../header/Runway.h"
#include "../header/Exceptions.h"
#include "../header/JsonUtils.h"
#include <iostream>

Runway::Runway(std::string runwayID_, const double& runwayLength_, const double& runwayWidth_, int runwayCondition_ = 0,
                const bool& runwayInUse_ = true) :
                runwayID{std::move(runwayID_)},
                runwayLength{runwayLength_},
                runwayWidth{runwayWidth_},
                runwayCondition{runwayCondition_},
                runwayInUse{runwayInUse_}
{
    if (runwayID.empty()) throw InvalidObjectCreation("Runway", "runwayID");
    if (runwayLength < 400) throw InvalidObjectCreation("Runway", "runwayLength");
    if (runwayWidth < 10) throw InvalidObjectCreation("Runway", "runwayWidth");
};
Runway::Runway(const Runway& other)
    : runwayID{other.runwayID},
      runwayLength{other.runwayLength},
      runwayWidth{other.runwayWidth},
      runwayCondition{other.runwayCondition},
      runwayInUse{other.runwayInUse}{}
Runway& Runway::operator=(const Runway& other)
{
    if (this != &other)
    {
        runwayID = other.runwayID;
        runwayLength = other.runwayLength;
        runwayWidth = other.runwayWidth;
        runwayCondition = other.runwayCondition;
        runwayInUse = other.runwayInUse;
    }
    return *this;
}
Runway::Runway(Runway&& other) noexcept
    : runwayID{std::move(other.runwayID)},
      runwayLength{other.runwayLength},
      runwayWidth{other.runwayWidth},
      runwayCondition{other.runwayCondition},
      runwayInUse{other.runwayInUse}{}
Runway& Runway::operator=(Runway&& other) noexcept
{
    if (this != &other)
    {
        runwayID = std::move(other.runwayID);
        runwayLength = other.runwayLength;
        runwayWidth = other.runwayWidth;
        runwayCondition = other.runwayCondition;
        runwayInUse = other.runwayInUse;
        other.runwayLength = 0;
        other.runwayWidth = 0;
        other.runwayInUse = false;
    }
    return *this;
}
Runway::~Runway() = default;
std::ostream& operator<<(std::ostream& os, const Runway& rw)
{
    os << "Runway " << rw.runwayID << "\n";
    os << "==========================================\n";
    os << "Runway length: " << rw.runwayLength << " m\n";
    os << "Runway width: " << rw.runwayWidth << " m\n";
    switch (rw.runwayCondition)
    {
        case 1:
            os << "Runway condition: WET\n";
            break;
        default:
            os << "Runway condition: DRY\n";
            break;
    }
    if (rw.runwayInUse)
        os << "Runway status: IN USE\n\n";
    else
        os << "Runway status: NOT IN USE\n\n";

    return os;
}
double Runway::getWidth() const {return this->runwayWidth;}
int Runway::calculateRwDirection() const
{
    std::string rwDirection = this->runwayID.substr(2, 2);
    int direction = std::stoi(rwDirection);
    return direction;
}
bool Runway::getRwStatus() const {return this->runwayInUse;}
double Runway::runwayFactorDeduction() const
{
    switch(runwayCondition)
    {
        case 0: return 1;
        case 1: return 1.20;
        default: return 1;
    }
}
bool Runway::runwayCodeMatch(const std::string& testValue) const {return testValue == runwayID;}
//a runway is too short for takeoff if the takeoffDistance + 0.15 * takeoffDistance > runwayLength
bool Runway::runwayTooShortTakeoff(const double& takeoffDistance) const {return runwayLength < takeoffDistance * TAKEOFF_SAFETY_FACTOR;}
//a runway is too short for landing if the landingDistance + 0.60 * landingDistance > runwayLength
bool Runway::runwayTooShortLanding(const double& landingDistance) const {return runwayLength < landingDistance * LANDING_SAFETY_FACTOR;}
void Runway::readFromJson(const nlohmann::json& obj)
{
    runwayID = readAttribute<std::string>(obj, "runwayID");
    runwayLength = readAttribute<double>(obj, "runwayLength");
    runwayWidth = readAttribute<double>(obj, "runwayWidth");
    runwayCondition = readAttribute<int>(obj, "runwayCondition");
    runwayInUse = readAttribute<bool>(obj, "runwayInUse");
}







