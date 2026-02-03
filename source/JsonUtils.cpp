#include "../header/JsonUtils.h"
#include <nlohmann/json.hpp>

#include "../header/Exceptions.h"

template <typename T> T readAttribute(const nlohmann::json& obj, const std::string& key)
{
    if (!obj.contains(key))
        throw JsonFaultyRead(key);
    return obj.at(key).get<T>();
}

template <typename T> void writeAttribute(nlohmann::json& obj, const std::string& key, const T& writeValue)
{
    obj[key] = writeValue;
}
