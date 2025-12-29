#include "../header/Exceptions.h"

AppException::AppException(const std::string& errorMessage) : runtime_error{errorMessage} {}
JsonFaultyRead::JsonFaultyRead(const std::string& attribute) :
                        AppException{"Attribute " + attribute + " is invalid!"} {}
InvalidFile::InvalidFile(const std::string& file) : AppException{"File " + file + " could not be opened or it does not exist"}{}
InvalidObjectCreation::InvalidObjectCreation(const std::string& objectType, const std::string& invalidAttribute):
                        AppException{"Object of type [" + objectType + "] could not be created! " +
                                        "Attribute [" + invalidAttribute + "] is invalid!"} {}
InvalidFlightPlanParameters::InvalidFlightPlanParameters(const std::string& message) :
                        AppException{"Flight plan error: " + message}{}





