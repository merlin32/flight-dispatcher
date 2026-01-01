#include "../header/FighterJet.h"
#include "../header/JsonUtils.h"
#include <nlohmann/json.hpp>
#include <iostream>

FighterJet::FighterJet(const std::string& category_,
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
             const double& maxCannonAmmoWeight_) :
                Aircraft{category_, type_, range_, cruisingSpeed_,
                    wingspan_, maxTakeoffWeight_, maxPayload_, emptyWeight_, fuelCapacity_,
                    fuelBurnClimb_, fuelBurnCruise_, fuelBurnDescent_, maxCruisingAltitude_,
                    fuelBurnIdle_, fuelBurnLowAltitude_, maxFreight_, takeoffReferenceDist_,
                    climbRate_, descentRate_, climbSpeed_, minimumFlightDuration_},
                    maxNumberOfPilots{maxNumberOfPilots_}, maxMissileCount{maxMissileCount_},
                    maxMissileWeight{maxMissileWeight_},maxCannonAmmoWeight{maxCannonAmmoWeight_}{}
std::shared_ptr<Aircraft> FighterJet::clone() const {return std::make_shared<FighterJet>(*this);}
double FighterJet::calculatePayload_() const
{
    return numberOfPilots * PILOT_WEIGHT + missileCount * weightPerMissile + cannonAmmoWeight;
}
double FighterJet::calculateFreight_() const
{
    return missileCount * weightPerMissile + cannonAmmoWeight;
}
void FighterJet::readFromJson_(const nlohmann::json& obj)
{
    maxNumberOfPilots = readAttribute<int>(obj, "maxNumberOfPilots");
    maxMissileCount = readAttribute<int>(obj, "maxMissileCount");
    maxMissileWeight = readAttribute<double>(obj, "maxMissileWeight");
    maxCannonAmmoWeight = readAttribute<double>(obj, "maxCannonAmmoWeight");
}
void FighterJet::display(std::ostream &os) const
{
    os << "Maximum number of pilots: " << maxNumberOfPilots << '\n';
    os << "Maximum missile count: " << maxMissileCount << '\n';
    os << "Maximum missile weight: " << maxMissileWeight << '\n';
    os << "Maximum cannon ammo weight: " << maxCannonAmmoWeight << '\n';
}
bool FighterJet::isDataValid_() const
{
    if (maxPilotCountExceeded() == true)
    {
        std::cerr << "Maximum number of pilots exceeded\n";
        return false;
    }
    if (maxMissileCountExceeded() == true)
    {
        std::cerr << "Maximum number of missiles exceeded\n";
        return false;
    }
    if (maxMissileWeightExceeded() == true)
    {
        std::cerr << "Maximum missile weight exceeded\n";
        return false;
    }
    if (maxCannonAmmoWeightExceeded() == true)
    {
        std::cerr << "Maximum cannon ammo weight exceeded\n";
        return false;
    }
    return true;
}
bool FighterJet::maxPilotCountExceeded() const {return numberOfPilots > maxNumberOfPilots;}
bool FighterJet::maxMissileCountExceeded() const {return missileCount > maxMissileCount;}
bool FighterJet::maxMissileWeightExceeded() const {return weightPerMissile > maxMissileWeight;}
bool FighterJet::maxCannonAmmoWeightExceeded() const {return cannonAmmoWeight > maxCannonAmmoWeight;}
void FighterJet::fighterJetInit(const int& numberOfPilots_, const int& missileCount_,
                                const double& weightPerMissile_, const double& cannonAmmoWeight_)
{
    numberOfPilots = numberOfPilots_;
    missileCount = missileCount_;
    weightPerMissile = weightPerMissile_;
    cannonAmmoWeight = cannonAmmoWeight_;
}








