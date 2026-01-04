#include "../header/Menu.h"
#include "../header/FuelManagement.h"
#include "../header/PerformanceCalculation.h"
#include "../header/AircraftFactory.h"
#include "../header/CargoAircraft.h"
#include "../header/Exceptions.h"
#include "../header/JsonUtils.h"
#include "../header/Waypoint.h"
#include <fstream>
#include <nlohmann/json.hpp>

#include "../header/FighterJet.h"
#include "../header/VectorUtils.h"

void Menu::populateAircrafts(std::ifstream aircraftsJson)
{
    nlohmann::json data = nlohmann::json::parse(aircraftsJson);
    for (const auto& i : data)
    {
        if (!i.contains("category") || !i["category"].is_string())
            throw JsonFaultyRead("category");
        std::string category = i["category"];
        std::shared_ptr<Aircraft> temp = AircraftFactory::createAircraft(i, category);
        if (temp)
            aircraftsList.push_back(temp);

    }
    aircraftsJson.close();
    sortClassArray<std::shared_ptr<Aircraft>>(aircraftsList);
}
void Menu::populateAirports(std::ifstream airportsJson)
{
    nlohmann::json data = nlohmann::json::parse(airportsJson);
    for (const auto& i : data)
    {
        Airport ap;
        ap.readFromJson(i);
        airportsList.push_back(ap);
    }
    airportsJson.close();
    sortClassArray<Airport>(airportsList);
}
void Menu::populateWaypoints(std::ifstream waypointsJson)
{
    nlohmann::json data = nlohmann::json::parse(waypointsJson);
    for (const auto& i : data)
    {
            Waypoint wp;
            wp.readFromJson(i);
            waypointsList.push_back(wp);
    }
    waypointsJson.close();
    sortClassArray<Waypoint>(waypointsList);
}
void Menu::populateAdjacencyList(std::ifstream waypointsAdjacencyJson)
{
    nlohmann::json data = nlohmann::json::parse(waypointsAdjacencyJson);
    for (auto it = data.begin(); it != data.end(); it++)
    {
        const std::string& waypointCode = it.key();
        std::vector<std::string> connections = it.value().get<std::vector<std::string>>();
        waypointsAdjacencyList[waypointCode] = connections;
    }
    waypointsAdjacencyJson.close();
}


void Menu::initLocalData()
{
    std::ifstream aircraftsJson;
    std::ifstream airportsJson;
    std::ifstream waypointsJson;
    std::ifstream waypointsAdjacencyJson;
    aircraftsJson.open("aircrafts.json");
    airportsJson.open("airports.json");
    waypointsJson.open("waypoints.json");
    waypointsAdjacencyJson.open("waypointsAdjacency.json");
    if (!aircraftsJson.is_open())
        throw InvalidFile("aircrafts.json");
    if (!airportsJson.is_open())
        throw InvalidFile("airports.json");
    if (!waypointsJson.is_open())
        throw InvalidFile("waypoints.json");
    if (!waypointsAdjacencyJson.is_open())
        throw InvalidFile("waypointsAdjacency.json");
    populateAircrafts(std::move(aircraftsJson));
    populateAirports(std::move(airportsJson));
    populateWaypoints(std::move(waypointsJson));
    populateAdjacencyList(std::move(waypointsAdjacencyJson));
}
void Menu::manualWaypointSelection(const std::string& departIcao, const std::string& arrivalIcao,
                                    std::vector<Waypoint>& routeWaypoints)
{
    //waypoints selection
    //displaying all the available waypoints
    std::cout << "Available waypoints: \n";
    for (const auto& i : waypointsList)
    {
        if (i.waypointIsAirport() == false)
        {
            std::cout << '\t';
            i.displayWaypointCode();
            std::cout << '\n';
        }
    }
    std::cout << '\n';
    //first, the departure airport is inserted into routeWaypoints, than the user enters the desired waypoints
    //to mark the end, the user must type "end"
    //the arrival airport waypoint is then inserted into the routeWaypoints
    //the program also checks whether the selected waypoint exists or not
    //for each waypoint, except the first one, we calculate its distance to the previous one
    std::cout << "================================\n";
    std::cout << "===== Waypoints selection ======\n";
    std::cout << "================================\n";
    std::cout << "Type (end) to stop selection!\n";
    std::string currentWaypoint;
    Waypoint departureWaypoint;
    Waypoint arrivalWaypoint;
    int counter = 1;
    if (Waypoint::findWaypoint(waypointsList, departIcao, departureWaypoint) == true)
        routeWaypoints.push_back(departureWaypoint);
    while (true)
    {
        std::cout << "Waypoint " << counter << ": ";
        std::cin >> currentWaypoint;
        if (currentWaypoint == "end")
            break;
        Waypoint temp;
        if (Waypoint::findWaypoint(waypointsList, currentWaypoint, temp))
        {
            routeWaypoints.push_back(temp);
            counter++;
        }
    }
    if (Waypoint::findWaypoint(waypointsList, arrivalIcao, arrivalWaypoint) == true)
        routeWaypoints.push_back(arrivalWaypoint);
    for (size_t i = 1; i < routeWaypoints.size(); i++)
        Waypoint previous = routeWaypoints[i-1];
}
void Menu::automaticWaypointSelection(const std::string& departIcao, const std::string& arrivalIcao,
                                        std::vector<Waypoint>& routeWaypoints)
{
    Waypoint departureWaypoint;
    Waypoint arrivalWaypoint;
    if (Waypoint::findWaypoint(waypointsList, departIcao, departureWaypoint) == false)
        throw AppException("Invalid waypoint");
    if (Waypoint::findWaypoint(waypointsList, arrivalIcao, arrivalWaypoint) == false)
        throw AppException("Invalid waypoint");
    routeWaypoints = Waypoint::pathFinder(departureWaypoint, arrivalWaypoint, waypointsList, waypointsAdjacencyList);
}

void Menu::flpCreation()
{
    //flight plan creation
    std::cout << "================================\n";
    std::cout << "===== Flight plan creation =====\n";
    std::cout << "================================\n";
    std::cout << "Callsign: ";
    std::string callSgn;
    std::cin >> callSgn;
    //listing all available airports
    std::cout << "Available airports: \n";
    for (const auto& i : airportsList)
    {
        std::cout <<'\t';
        i.displayIcaoCode();
        std::cout << '\n';
    }
    std::cout << '\n';
    //departure selection. If the ICAO code is not present in airportsList, the user must enter again a valid code
    Airport depart;
    std::string departIcao;
    while (true)
    {
        std::cout << "Departure: ";
        std::cin >> departIcao;
        if (Airport::findAirport(airportsList, departIcao, depart) == true)
            break;
    }
    //arrival selection. If the ICAO code is not present in airportsList, the user must enter again a valid code
    Airport arrival;
    std::string arrivalIcao;
    while (true)
    {
        std::cout << "Arrival: ";
        std::cin >> arrivalIcao;
        if (Airport::findAirport(airportsList, arrivalIcao, arrival) == true)
            break;
    }
    //displaying available runways at the departure airport
    depart.displayRunways();
    //departure runway selection.
    //the runway is being checked and if it doesn't exist, the user must enter again a valid runway code
    std::string departRw;
    while (true)
    {
        std::cout << "Departing runway: ";
        std::cin >> departRw;
        if (Airport::validRunway(departRw, depart) == true)
            break;
    }
    //displaying available runways at the arrival airport
    arrival.displayRunways();
    //arrival runway selection.
    //the runway is being checked and if it doesn't exist, the user must enter again a valid runway code
    std::string arrivalRw;
    while (true)
    {
        std::cout << "Arrival runway: ";
        std::cin >> arrivalRw;
        if (Airport::validRunway(arrivalRw, arrival) == true)
            break;
    }
    //waypoint selection
    std::vector<Waypoint> routeWaypoints;
    char option;
    std::cout << "Waypoint selection: manual or automatic? [m/a]: ";
    std::cin >> option;
    if (option == 'm')
        manualWaypointSelection(departIcao, arrivalIcao, routeWaypoints);
    else if (option == 'a')
        automaticWaypointSelection(departIcao, arrivalIcao, routeWaypoints);
    else
        throw AppException("Invalid option for waypoint selection");
    //displaying all the available planes
    std::cout << "Available planes: \n";
    for (const auto& i : aircraftsList)
    {
        std::cout << '\t';
        i->displayAircraftType();
        std::cout << '\n';
    }
    std::cout << '\n';
    //aircraft selection
    std::shared_ptr<Aircraft> ac;
    while (true)
    {
        std::cout << "Aircraft type: ";
        std::string acType;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //buffer clear
        std::getline(std::cin, acType);
        if (Aircraft::findAircraft(aircraftsList, acType, ac) == true)
            break;
    }
    while (true)
    {
        ac->aircraftCategoryInit();
        if (ac->isDataValid() == true)
            break;
    }
    if (ac->categoryMatch("fighter jet") == true)
    {
        auto fighterJet = std::dynamic_pointer_cast<FighterJet>(ac);
        if (fighterJet)
        {
            std::cout << "Note that the values entered for payload and freight calculation might lead to an invalid flight plan!\n";
            std::cout << "Reason: The aircraft's performance parameters are based on combat conditions.\n";
            std::cout << "Suggestion: Enter lower values for long flights.\n";
            std::cout << "Want to enter those values again?[y/n]: ";
            char choice;
            std::cin >> choice;
            if (choice == 'y')
                while (true)
                {
                    ac->aircraftCategoryInit();
                    if (ac->isDataValid() == true)
                        break;
                }
            std::cout << "Suggestion: for long flights, it is recommended to enter the values for contingency and reserve time!\n";
        }
    }
    //cruising altitude selection
    int cruiseAltInput;
    while (true)
        if (readAutoFields("Cruise altitude: ", cruiseAltInput) == true)
            break;
    //FuelManagement input data
    std::cout << "==================\n";
    std::cout << "== Fuel entries ==\n";
    std::cout << "==================\n";

    double ctgPctInput;
    while (true)
        if (readAutoFields("Contingency: ", ctgPctInput) == true)
            break;
    int rsvTimeInput;
    while (true)
        if (readAutoFields("Reserve Time: ", rsvTimeInput) == true)
            break;
    double txFuelInput;
    while (true)
        if (readAutoFields("Taxi Fuel: ", txFuelInput) == true)
            break;
    double blkFuelInput;
    while (true)
        if (readAutoFields("Block Fuel: ", blkFuelInput) == true)
            break;
    FuelManagement fuelPlanning{ctgPctInput, rsvTimeInput, txFuelInput, blkFuelInput};
    //performance calculation data init
    PerformanceCalculation perfCalc;
    perfCalc.setPayload(ac);
    //flight plan creation
    try
    {
        Route rt1{ callSgn, depart, arrival,
        departRw, arrivalRw,
             routeWaypoints, ac, fuelPlanning, perfCalc, cruiseAltInput};
        rt1.routeInit();
        std::cout << rt1;
        flightPlans.emplace_back(std::move(rt1));
        continuationConfirm();
    }
    catch (const InvalidFlightPlanParameters& err)
    {
        std::cerr << err.what() << '\n';
    }
}

void Menu::flpSelection()
{
    std::cout << "=======================================\n";
    std::cout << "===== Flight Plan Selection Menu  =====\n";
    std::cout << "=======================================\n\n";
    for (size_t i = 0; i < flightPlans.size(); i++)
    {
        std::cout << i + 1 << ") ";
        flightPlans[i].displayShortInfo();
    }
    std::cout << flightPlans.size() + 1 << ") Back\n\n";
    std::cout << "|>";
    size_t option;
    std::cin >> option;
    try
    {
        if (option > flightPlans.size() + 1)
            throw AppException("No such option available");
        if (option == flightPlans.size() + 1)
            return;

        std::cout << flightPlans[option - 1];
        continuationConfirm();
    }
    catch (const AppException& err)
    {
        std::cerr << err.what() << '\n';
    }
}


void Menu::mainMenu()
{
    std::cout << "=======================================\n";
    std::cout << "==== Flight Dispatcher - Main Menu ====\n";
    std::cout << "=======================================\n\n";
    std::cout << "\t1) Create new flight plan\n";
    std::cout << "\t2) Open existing flight plan\n";
    std::cout << "\t3) Exit\n";
    std::cout << "|>";
    unsigned short int option;
    std::cin >> option;
    switch (option)
    {
        case 1: flpCreation(); break;
        case 2: flpSelection(); break;
        case 3: exit(0);
        default: std::cerr << "Unknown option! Please enter a valid option!\n"; break;
    }
    std::cout << "\n\n\n";
}

void Menu::continuationConfirm()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
bool Menu::readAutoFields(const std::string& displayMessage, int& field)
{
    std::cout << displayMessage;
    std::string inputValue;
    std::cin >> inputValue;
    try
    {
        if (inputValue != "auto")
            field = std::stoi(inputValue);
        else
            field = 0;
        return true;
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << '\n';
        std::cerr << "Input error: enter <auto> or a number\n";
        return false;
    }
}
bool Menu::readAutoFields(const std::string& displayMessage, double& field)
{
    std::cout << displayMessage;
    std::string inputValue;
    std::cin >> inputValue;
    try
    {
        if (inputValue != "auto")
            field = std::stod(inputValue);
        else
            field = 0;
        return true;
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << '\n';
        std::cerr << "Input error: enter <auto> or a number\n";
        return false;
    }
}


