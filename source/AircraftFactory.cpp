#include "../header/AircraftFactory.h"
#include "../header/PassengerAircraft.h"
#include "../header/CargoAircraft.h"
#include "../header/GeneralAviationAircraft.h"
#include "../header/Exceptions.h"
#include <nlohmann/json.hpp>

std::shared_ptr<Aircraft> AircraftFactory::createAircraft(const nlohmann::json& obj)
{

    if (!obj.contains("category") || !obj["category"].is_string())
        throw JsonFaultyRead("category");
    std::string category = obj["category"];
    std::shared_ptr<Aircraft> plane;

    if (category == "passenger") plane = std::make_shared<PassengerAircraft>();
    else if (category == "cargo") plane = std::make_shared<CargoAircraft>();
    else if (category == "general aviation") plane = std::make_shared<GeneralAviationAircraft>();
    else throw JsonFaultyRead("category");

    if (plane) plane->readFromJson(obj);
    return plane;

}
