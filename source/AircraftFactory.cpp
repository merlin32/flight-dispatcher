#include "../header/AircraftFactory.h"
#include "../header/PassengerAircraft.h"
#include "../header/CargoAircraft.h"
#include "../header/GeneralAviationAircraft.h"

std::shared_ptr<Aircraft> AircraftFactory::createAircraft(const nlohmann::json& obj)
{
    std::string category = obj["category"];
    std::shared_ptr<Aircraft> plane;

    if (category == "passenger") plane = std::make_shared<PassengerAircraft>();
    if (category == "cargo") plane = std::make_shared<CargoAircraft>();
    if (category == "general aviation") plane = std::make_shared<GeneralAviationAircraft>();

    if (plane) plane->readFromJson(obj);
    return plane;
}