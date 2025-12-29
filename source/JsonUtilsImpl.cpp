#include "JsonUtils.cpp"

template int readAttribute<int>(const nlohmann::json& obj, const std::string& key);
template std::string readAttribute<std::string>(const nlohmann::json& obj, const std::string& key);
template double readAttribute<double>(const nlohmann::json& obj, const std::string& key);
template unsigned short int readAttribute<unsigned short int>(const nlohmann::json& obj, const std::string& key);
template bool readAttribute<bool>(const nlohmann::json& obj, const std::string& key);
