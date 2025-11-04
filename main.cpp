#include "header/Menu.h"
#include <nlohmann/json.hpp>

int main() {
    std::ifstream waypoints;
    waypoints.open("waypoints.json");
    nlohmann::json data = nlohmann::json::parse(waypoints);
    Menu mainMenu;
    mainMenu.initLocalData();
    mainMenu.flpCreation();
    return 0;
}
