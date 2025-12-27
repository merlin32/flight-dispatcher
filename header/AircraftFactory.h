
#ifndef AIRCRAFTFACTORY_H
#define AIRCRAFTFACTORY_H

#include "Aircraft.h"
#include <memory>

class AircraftFactory
{
public:
    static std::shared_ptr<Aircraft> createAircraft(const nlohmann::json& obj);
};
#endif //AIRCRAFTFACTORY_H
