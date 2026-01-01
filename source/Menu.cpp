#include "../header/Menu.h"
#include "../header/FuelManagement.h"
#include "../header/PerformanceCalculation.h"
#include "../header/AircraftFactory.h"
#include "../header/CargoAircraft.h"
#include "../header/GeneralAviationAircraft.h"
#include "../header/PassengerAircraft.h"
#include "../header/FighterJet.h"
#include "../header/Exceptions.h"
#include "../header/JsonUtils.h"
#include "../header/Waypoint.h"
#include <fstream>
#include <nlohmann/json.hpp>

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
    std::sort(aircraftsList.begin(),aircraftsList.end(), Aircraft::compareAircraftTypes);
}
void Menu::populateAirports(std::ifstream airportsJson)
{
    nlohmann::json data = nlohmann::json::parse(airportsJson);
    for (const auto& i : data)
    {
        std::vector<Runway> runwaysList;
        if (!i.contains("airportRunways"))
            throw JsonFaultyRead("airportRunways");
        for (const auto& j : i["airportRunways"])
        {
            Runway rw{
                readAttribute<std::string>(j, "runwayID"),
                readAttribute<double>(j, "runwayLength"),
                readAttribute<double>(j, "runwayWidth"),
                readAttribute<int>(j, "runwayCondition"),
                readAttribute<bool>(j, "runwayInUse")
            };
            runwaysList.push_back(rw);
        }
        if (!i.contains("metar"))
            throw JsonFaultyRead("metar");
        Metar mt{
            readAttribute<std::string>(i["metar"][0], "airportIcao"),
            readAttribute<std::string>(i["metar"][0], "dateAndTime"),
            readAttribute<std::string>(i["metar"][0], "windInfo"),
            readAttribute<std::string>(i["metar"][0], "visibility"),
            readAttribute<std::string>(i["metar"][0], "specialConditions"),
            readAttribute<std::string>(i["metar"][0], "cloudsInfo"),
            readAttribute<short int>(i["metar"][0], "temperature"),
            readAttribute<short int>(i["metar"][0], "dewpoint"),
            readAttribute<unsigned short int>(i["metar"][0], "qnh"),
            readAttribute<std::string>(i["metar"][0], "additionalChanges")
        };
        Airport ap{
            readAttribute<std::string>(i, "icaoCode"),
            readAttribute<int>(i, "elevation"),
            readAttribute<std::string>(i, "airportName"),
            readAttribute<std::string>(i, "iataCode"),
            runwaysList,
            mt
        };
        airportsList.push_back(ap);
    }
    airportsJson.close();
    std::sort(airportsList.begin(), airportsList.end(), Airport::compareAirportsIcao);
}
void Menu::populateWaypoints(std::ifstream waypointsJson)
{
    nlohmann::json data = nlohmann::json::parse(waypointsJson);
    for (const auto& i : data)
    {
            Waypoint wp{
                readAttribute<std::string>(i, "waypointCode"),
                readAttribute<double>(i, "longitude"),
                readAttribute<double>(i, "latitude"),
                readAttribute<int>(i, "maxAltitude"),
                readAttribute<int>(i, "minAltitude"),
                readAttribute<bool>(i, "weatherAffected")
            };
            waypointsList.push_back(wp);
    }
    waypointsJson.close();
    std::sort(waypointsList.begin(), waypointsList.end(), Waypoint::compareWaypointCodes);
}
void Menu::populateAdjacencyList(std::ifstream waypointsAdjacencyJson)
{
    nlohmann::json data = nlohmann::json::parse(waypointsAdjacencyJson);
    for (auto it = data.begin(); it != data.end(); it++)
    {
        std::string waypointCode = it.key();
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
    if (Waypoint::validWaypoint(waypointsList, departIcao, departureWaypoint) == true)
        routeWaypoints.push_back(departureWaypoint);
    while (true)
    {
        std::cout << "Waypoint " << counter << ": ";
        std::cin >> currentWaypoint;
        if (currentWaypoint == "end")
            break;
        Waypoint temp;
        if (Waypoint::validWaypoint(waypointsList, currentWaypoint, temp))
        {
            routeWaypoints.push_back(temp);
            counter++;
        }
    }
    if (Waypoint::validWaypoint(waypointsList, arrivalIcao, arrivalWaypoint) == true)
        routeWaypoints.push_back(arrivalWaypoint);
    for (size_t i = 1; i < routeWaypoints.size(); i++)
        Waypoint previous = routeWaypoints[i-1];
}
void Menu::automaticWaypointSelection(const std::string& departIcao, const std::string& arrivalIcao,
                                        std::vector<Waypoint>& routeWaypoints)
{
    Waypoint departureWaypoint;
    Waypoint arrivalWaypoint;
    if (Waypoint::validWaypoint(waypointsList, departIcao, departureWaypoint) == false)
        throw AppException("Invalid waypoint");
    if (Waypoint::validWaypoint(waypointsList, arrivalIcao, arrivalWaypoint) == false)
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
    //departure selection. If the ICAO code is not present in airportsList, the user must enter again a valid code
    Airport depart;
    std::string departIcao;
    while (true)
    {
        std::cout << "Departure: ";
        std::cin >> departIcao;
        if (Airport::validAirport(airportsList, departIcao, depart) == true)
            break;
    }
    //arrival selection. If the ICAO code is not present in airportsList, the user must enter again a valid code
    Airport arrival;
    std::string arrivalIcao;
    while (true)
    {
        std::cout << "Arrival: ";
        std::cin >> arrivalIcao;
        if (Airport::validAirport(airportsList, arrivalIcao, arrival) == true)
            break;
    }
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
    //aircraft selection
    std::shared_ptr<Aircraft> ac;
    while (true)
    {
        std::cout << "Aircraft type: ";
        std::string acType;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //buffer clear
        std::getline(std::cin, acType);
        if (Aircraft::validAircraft(aircraftsList, acType, ac) == true)
            break;
    }

    if (ac->categoryMatch("passenger") == true)
    {
        auto passengerAc = std::dynamic_pointer_cast<PassengerAircraft>(ac);
        if (passengerAc)
        {
            int freight;
            int passengers;
            while (true)
            {
                std::cout << "Freight: ";
                std::cin >> freight;
                std::cout << "Passengers: ";
                std::cin >> passengers;
                if (passengerAc->isDataValid() == true)
                    break;
            }
            passengerAc->setFreight(freight);
            passengerAc->setPassengerNumber(passengers);
        }
    }
    if (ac->categoryMatch("cargo") == true)
    {
        auto cargoAc = std::dynamic_pointer_cast<CargoAircraft>(ac);
        if (cargoAc)
        {
            int containersNum;
            std::vector<double> containersWeights{};
            while (true)
            {
                std::cout << "Number of containers: ";
                std::cin >> containersNum;
                std::cout << "Enter each container's weight: \n";
                for (int i = 0; i < containersNum; i++)
                {
                    double temp;
                    std::cout << "Container " << i + 1 << ": ";
                    std::cin >> temp;
                    containersWeights.push_back(temp);
                }
                if (cargoAc->isDataValid() == true)
                    break;
            }
            cargoAc->setContainersNum(containersNum);
            cargoAc->setContainersWeights(containersWeights);
        }
    }
    if (ac->categoryMatch("general aviation") == true)
    {
        auto generalAvAc = std::dynamic_pointer_cast<GeneralAviationAircraft>(ac);
        if (generalAvAc)
        {
            int pilotsCount;
            int passengersNumber;
            double baggageWeight;
            while (true)
            {
                std::cout << "Number of pilots: ";
                std::cin >> pilotsCount;
                std::cout << "Passengers: ";
                std::cin >> passengersNumber;
                std::cout << "Baggage quantity: ";
                std::cin >> baggageWeight;
                if (generalAvAc->isDataValid() == true)
                    break;
            }
            generalAvAc->setPilotsCount(pilotsCount);
            generalAvAc->setPassengersNumber(passengersNumber);
            generalAvAc->setBaggageWeight(baggageWeight);
        }
    }
    if (ac->categoryMatch("fighter jet") == true)
    {
        //in this case, to obtain a result, the aircraft's parameters have been set to "dry power" values
        //dry power = normal flight, similar to any other aircraft
        auto fighterAc = std::dynamic_pointer_cast<FighterJet>(ac);
        if (fighterAc)
        {
            int numberOfPilots;
            int numberOfMissiles;
            double missileWeight;
            double cannonAmmoWeight;
            while (true)
            {
                std::cout << "Number of pilots: ";
                std::cin >> numberOfPilots;
                std::cout << "Number of missiles: ";
                std::cin >> numberOfMissiles;
                std::cout << "Missile weight: ";
                std::cin >> missileWeight;
                std::cout << "Cannon ammo weight: ";
                std::cin >> cannonAmmoWeight;
                fighterAc->fighterJetInit(numberOfPilots, numberOfMissiles, missileWeight, cannonAmmoWeight);
                if (fighterAc->isDataValid() == true)
                    break;
            }

        }
    }
    //cruising altitude selection
    std::cout << "Cruise altitude: ";
    std::string cruiseAlt;
    int cruiseAltInput = 0;
    std::cin >> cruiseAlt;
    if (cruiseAlt != "auto")
        cruiseAltInput = std::stoi(cruiseAlt);
    //FuelManagement input data
    std::cout << "==================\n";
    std::cout << "== Fuel entries ==\n";
    std::cout << "==================\n";
    std::cout << "Contingency: ";
    std::string fieldEntry;
    double ctgPctInput;
    std::cin >> fieldEntry;
    if (fieldEntry != "auto")
        ctgPctInput = std::stod(fieldEntry);
    else
        ctgPctInput = 0;
    std::cout << "Reserve Time: ";
    int rsvTimeInput;
    std::cin >> fieldEntry;
    if (fieldEntry != "auto")
        rsvTimeInput = std::stoi(fieldEntry);
    else
        rsvTimeInput = 0;
    std::cout << "Taxi Fuel: ";
    double txFuelInput;
    std::cin >> fieldEntry;
    if (fieldEntry != "auto")
        txFuelInput = std::stod(fieldEntry);
    else
        txFuelInput = 0;
    std::cout << "Block Fuel: ";
    double blkFuelInput;
    std::cin >> fieldEntry;
    if (fieldEntry != "auto")
        blkFuelInput = std::stod(fieldEntry);
    else
        blkFuelInput = 0;
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

void Menu::continuationConfirm() const
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
