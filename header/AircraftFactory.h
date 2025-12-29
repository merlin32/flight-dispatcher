
#ifndef AIRCRAFTFACTORY_H
#define AIRCRAFTFACTORY_H

#include "Aircraft.h"

class AircraftFactory
{
public:
    static std::shared_ptr<Aircraft> createAircraft(const nlohmann::json& obj, const std::string& category);
};
#endif //AIRCRAFTFACTORY_H
