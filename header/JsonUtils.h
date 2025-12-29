
#ifndef JSONUTILS_H
#define JSONUTILS_H

#include <nlohmann/json_fwd.hpp>

template <typename T> T readAttribute(const nlohmann::json& obj, const std::string& key);

#endif //JSONUTILS_H
