#include "../header/Runway.h"

Runway::Runway(std::string runwayID_, const double& runwayLength_, const double& runwayWidth_, RwCond runwayCondition_, const bool& runwayInUse_) :
                runwayID{std::move(runwayID_)},
                runwayLength{runwayLength_},
                runwayWidth{runwayWidth_},
                runwayCondition{runwayCondition_},
                runwayInUse{runwayInUse_}{};
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
        case Dry:
            os << "Runway condition: DRY\n";
            break;
        case Wet:
            os << "Runway condition: WET\n";
            break;
    }
    if (rw.runwayInUse)
        os << "Runway status: IN USE\n\n";
    else
        os << "Runway status: NOT IN USE\n\n";

    return os;
}

double Runway::getLength() const {return this->runwayLength;}
double Runway::getWidth() const {return this->runwayWidth;}
std::string Runway::getRunwayID() const{return this->runwayID;}
int Runway::getRwDirection() const
{
    std::string rwDirection = this->runwayID.substr(2, 2);
    int direction = std::stoi(rwDirection);
    return direction;
}
int Runway::getRwCondition() const
{
    switch (this->runwayCondition)
    {
        case Dry: return 0;
        case Wet: return 1;
        default: return -1;
    }
}
bool Runway::getRwStatus() const {return this->runwayInUse;}




