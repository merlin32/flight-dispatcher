#include "VectorUtils.cpp"
#include "../header/Aircraft.h"
#include "../header/Airport.h"
#include "../header/Waypoint.h"

template void sortClassArray(std::vector<std::shared_ptr<Aircraft>>& unsortedArray);
template void sortClassArray(std::vector<Airport>& unsortedArray);
template void sortClassArray(std::vector<Waypoint>& unsortedArray);