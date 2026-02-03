
#ifndef JSONUTILS_H
#define JSONUTILS_H

#include <nlohmann/json_fwd.hpp>

template <typename T> T readAttribute(const nlohmann::json& obj, const std::string& key);
template <typename T> void writeAttribute(nlohmann::json& obj, const std::string& key, const T& writeValue);

#endif //JSONUTILS_H
