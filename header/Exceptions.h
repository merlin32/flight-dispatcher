

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class AppException : public std::runtime_error
{
    using std::runtime_error::runtime_error;
public:
    explicit AppException(const std::string& errorMessage);
};

class JsonFaultyRead : public AppException
{
public:
    explicit JsonFaultyRead(const std::string& attribute);
};

class InvalidFile : public AppException
{
public:
    explicit InvalidFile(const std::string& file);
};

class InvalidObjectCreation: public AppException
{
public:
    explicit InvalidObjectCreation(const std::string& objectType, const std::string& invalidAttribute);
};

class InvalidFlightPlanParameters : public AppException
{
public:
    explicit InvalidFlightPlanParameters(const std::string& message);
};

#endif //EXCEPTIONS_H
