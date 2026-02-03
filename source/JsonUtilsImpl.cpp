#include "JsonUtils.cpp"

//read
template int readAttribute<int>(const nlohmann::json& obj, const std::string& key);
template std::string readAttribute<std::string>(const nlohmann::json& obj, const std::string& key);
template double readAttribute<double>(const nlohmann::json& obj, const std::string& key);
template unsigned short int readAttribute<unsigned short int>(const nlohmann::json& obj, const std::string& key);
template bool readAttribute<bool>(const nlohmann::json& obj, const std::string& key);
template short int readAttribute<short int>(const nlohmann::json& obj, const std::string& key);
template std::vector<std::string> readAttribute<std::vector<std::string>>(const nlohmann::json& obj, const std::string& key);
template std::vector<double> readAttribute<std::vector<double>>(const nlohmann::json& obj, const std::string& key);

//write
template void writeAttribute<int>(nlohmann::json& obj, const std::string& key, const int& writeValue);
template void writeAttribute<std::string>(nlohmann::json& obj, const std::string& key, const std::string& writeValue);
template void writeAttribute<double>(nlohmann::json& obj, const std::string& key, const double& writeValue);
template void writeAttribute<unsigned short int>(nlohmann::json& obj, const std::string& key, const unsigned short int& writeValue);
template void writeAttribute<bool>(nlohmann::json& obj, const std::string& key, const bool& writeValue);
template void writeAttribute<short int>(nlohmann::json& obj, const std::string& key, const short int& writeValue);
template void writeAttribute<std::vector<std::string>>(nlohmann::json& obj, const std::string& key, const std::vector<std::string>& writeValue);
template void writeAttribute<std::vector<double>>(nlohmann::json& obj, const std::string& key, const std::vector<double>& writeValue);
