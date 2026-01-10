#include "VectorUtils.cpp"
#include "../header/Aircraft.h"
#include "../header/Airport.h"
#include "../header/Waypoint.h"

template void sortClassArray(std::vector<std::shared_ptr<Aircraft>>& unsortedArray);
template void sortClassArray(std::vector<Airport>& unsortedArray);
template void sortClassArray(std::vector<Waypoint>& unsortedArray);
template bool hasDigitsOnly(const std::string &container, const bool& isDouble);
template void validInputItem<int>(const std::string& message, int& parameter);
template void validInputItem<double>(const std::string& message, double& parameter);
template void validInputVector<double>(const std::string& message, std::vector<double>& parameter, const int& size);