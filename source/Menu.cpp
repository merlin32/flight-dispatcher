#include "../header/Menu.h"
#include "../header/FuelManagement.h"
#include "../header/PerformanceCalculation.h"
#include "../header/AircraftFactory.h"
#include "../header/CargoAircraft.h"
#include "../header/GeneralAviationAircraft.h"
#include "../header/PassengerAircraft.h"
#include "../header/Exceptions.h"
#include "../header/JsonUtils.h"
#include <fstream>
#include <nlohmann/json.hpp>

void Menu::populateAircrafts(std::ifstream aircraftsJson)
{
    nlohmann::json data = nlohmann::json::parse(aircraftsJson);
    for (const auto& i : data)
    {

        std::shared_ptr<Aircraft> temp = AircraftFactory::createAircraft(i);
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
            readAttribute<unsigned short int>(i, "elevation"),
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
void Menu::initLocalData()
{
    std::ifstream aircraftsJson;
    std::ifstream airportsJson;
    std::ifstream waypointsJson;
    aircraftsJson.open("aircrafts.json");
    airportsJson.open("airports.json");
    waypointsJson.open("waypoints.json");
    if (!aircraftsJson.is_open())
        throw InvalidFile("aircrafts.json");
    if (!airportsJson.is_open())
        throw InvalidFile("airports.json");
    if (!waypointsJson.is_open())
        throw InvalidFile("waypoints.json");
    populateAircrafts(std::move(aircraftsJson));
    populateAirports(std::move(airportsJson));
    populateWaypoints(std::move(waypointsJson));
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
    std::vector<Waypoint> routeWaypoints;
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
    {
        Waypoint previous = routeWaypoints[i-1];
        routeWaypoints[i].setDistanceToPrevious(previous);
    }

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

    if (ac->getCategory() == "passenger")
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
    if (ac->getCategory() == "cargo")
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
    if (ac->getCategory() == "general aviation")
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
    Route rt1{ callSgn, depart, arrival,
        departRw, arrivalRw,
             routeWaypoints, ac, fuelPlanning, perfCalc, cruiseAltInput};
    rt1.routeInit();
    std::cout << rt1;

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Menu::mainMenu()
{
    std::cout << "=======================================\n";
    std::cout << "==== Flight Dispatcher - Main Menu ====\n";
    std::cout << "=======================================\n\n";
    std::cout << "\t1) Create new flight plan\n";
    std::cout << "\t2) Open existing flight plan\n";
    std::cout << "\t3) Exit\n";
    unsigned short int option;
    std::cin >> option;
    switch (option)
    {
        case 1: flpCreation(); break;
        //case 2: accessFlp(); break;
        case 3: exit(0);
        default: std::cerr << "Unknown option! Please enter a valid option!\n"; break;
    }
    std::cout << "\n\n\n";
}