#include "../header/Runway.h"

Runway::Runway(std::string runwayID_, const int& runwayLength_, RwCond runwayCondition_, bool runwayInUse_) :
                runwayID{std::move(runwayID_)},
                runwayLength{runwayLength_},
                runwayCondition{runwayCondition_},
                runwayInUse{runwayInUse_}{};
Runway::Runway(const Runway& other) = default;
Runway::~Runway() = default;
std::ostream& operator<<(std::ostream& os, const Runway& rw)
{
    os << "Runway " << rw.runwayID << " information\n";
    os << "==========================================\n";
    os << "Runway length: " << rw.runwayLength << " m\n";
    switch (rw.runwayCondition)
    {
        case Dry:
            os << "Runway condition: DRY\n";
            break;
        case Wet:
            os << "Runway condition: WET\n";
            break;
    }
    switch (rw.runwayInUse)
    {
        case true:
            os << "Runway status: IN USE\n\n";
            break;
        case false:
            os << "Runway status: NOT IN USE\n\n";
            break;
    }
    return os;
}

int Runway::getLength() const {return this->runwayLength;}


