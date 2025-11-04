#include "../header/Menu.h"

#include "../header/FuelManagement.h"
#include "../header/PerformanceCalculation.h"

void Menu::populateAircrafts(std::ifstream aircraftsJson)
{
    nlohmann::json data = nlohmann::json::parse(aircraftsJson);
    for (const auto& i : data)
    {
        Aircraft ac{
            i["type"],
            i["range"],
            i["cruisingSpeed"],
            i["wingSpan"],
            i["maxTakeoffWeight"],
            i["maxPayload"],
            i["emptyWeight"],
            i["fuelCapacity"],
            i["fuelBurnClimb"],
            i["fuelBurnCruise"],
            i["fuelBurnDescent"],
            i["maxCruisingAltitude"],
            i["fuelBurnIdle"],
            i["fuelBurnLowAltitude"],
            i["maxFreight"],
            i["maxPassengerCount"],
            i["takeoffReferenceDist"],
            i["climbRate"],
            i["descentRate"],
            i["climbSpeed"],
            i["minimumFlightDuration"]
        };
        aircraftsList.push_back(ac);
    }
    aircraftsJson.close();
}
void Menu::populateAirports(std::ifstream airportsJson)
{
    nlohmann::json data = nlohmann::json::parse(airportsJson);
    for (const auto& i : data)
    {
        std::vector<Runway> runwaysList;
        for (const auto& j : i["airportRunways"])
        {
            Runway rw{
                j["runwayID"],
                j["runwayLength"],
                j["runwayWidth"],
                j["runwayCondition"],
                j["runwayInUse"]
            };
            runwaysList.push_back(rw);
        }
        Metar mt{
            i["airportWeather"][0]["weatherMetar"][0]["airportIcao"],
            i["airportWeather"][0]["weatherMetar"][0]["dateAndTime"],
            i["airportWeather"][0]["weatherMetar"][0]["windInfo"],
            i["airportWeather"][0]["weatherMetar"][0]["visibility"],
            i["airportWeather"][0]["weatherMetar"][0]["specialConditions"],
            i["airportWeather"][0]["weatherMetar"][0]["cloudsInfo"],
            i["airportWeather"][0]["weatherMetar"][0]["temperature"],
            i["airportWeather"][0]["weatherMetar"][0]["dewpoint"],
            i["airportWeather"][0]["weatherMetar"][0]["qnh"],
            i["airportWeather"][0]["weatherMetar"][0]["additionalChanges"]
        };
        Weather wh{
            i["airportWeather"][0]["weatherReportStart"],
            i["airportWeather"][0]["weatherReportEnd"],
            mt
        };
        Airport ap{
            i["icaoCode"],
            i["elevation"],
            i["airportName"],
            i["iataCode"],
            runwaysList,
            wh
        };
        airportsList.push_back(ap);
    }
    airportsJson.close();
}
void Menu::populateWaypoints(std::ifstream waypointsJson)
{
    nlohmann::json data = nlohmann::json::parse(waypointsJson);
    for (const auto& i : data)
    {
            Waypoint wp{
                i["waypointCode"],
                i["longitude"],
                i["latitude"],
                i["maxAltitude"],
                i["minAltitude"],
                i["weatherAffected"]
            };
            waypointsList.push_back(wp);
    }
    //waypointsJson.close();
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
    {
        std::cerr << "Error opening aircrafts.json!\n";
        return;
    }
    if (!airportsJson.is_open())
    {
        std::cerr << "Error opening airports.json!\n";
        return;
    }
    if (!waypointsJson.is_open())
    {
        std::cerr << "Error opening waypoints.json!\n";
        return;
    }
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
    std::cout << "Flight number: ";
    std::string fltNumber;
    std::cin >> fltNumber;
    std::cout << "Callsign: ";
    std::string callSgn;
    std::cin >> callSgn;
    //departure selection. if the ICAO code is not present in airportsList the program ends
    std::cout << "Departure: ";
    std::string departIcao;
    std::cin >> departIcao;
    Airport depart;
    bool found = false;
    for (const auto& i : airportsList)
        if (departIcao == i.getIcao())
        {
            found = true;
            depart = i;
            break;
        }
    if (found == false)
    {
        std::cerr << "Icao code not found in database\n";
        return;
    }
    //arrival selection. if the ICAO code is not present in airportsList the program ends
    found = false;
    Airport arrival;
    std::cout << "Arrival: ";
    std::string arrivalIcao;
    std::cin >> arrivalIcao;
    for (const auto& i : airportsList)
        if (arrivalIcao == i.getIcao())
        {
            found = true;
            arrival = i;
            break;
        }
    if (found == false)
    {
        std::cerr << "Icao code not found in database\n";
        return;
    }
    //departing runway: it must exist and it must be in use
    found = false;
    std::cout << "Departing runway: ";
    std::string departRw;
    std::cin >> departRw;
    for (const auto& i : depart.getAirportRunways())
    {
        if (departRw == i.getRunwayID() && i.getRwStatus())
            found = true;
    }
    if (found == false)
    {
        std::cerr << "Invalid runway selection\n";
        return;
    }
    //arrival runway: it must exist and it must be in use
    found = false;
    std::cout << "Arrival runway: ";
    std::string arrivalRw;
    std::cin >> arrivalRw;
    for (const auto& i : arrival.getAirportRunways())
    {
        if (arrivalRw == i.getRunwayID() && i.getRwStatus())
            found = true;
    }
    if (found == false)
    {
        std::cerr << "Invalid runway selection\n";
        return;
    }
    //waypoints selection
    //first, the departure airport is inserted into routeWaypoints, than the user enters the desired waypoints
    //to mark the end, the user must type "end"
    //the arrival airport waypoint is then inserted into the routeWaypoints
    //the program also checks whether the selected waypoint exists or not
    //for each waypoint we calculate its distance to the previous waypoint
    std::cout << "Enter waypoints: ";
    std::vector<Waypoint> routeWaypoints;
    std::string currentWaypoint;
    std::cin >> currentWaypoint;
    for (const auto& i : waypointsList)
        if (departIcao == i.getWaypointCode())
        {
            routeWaypoints.push_back(i);
            break;
        }
    while (currentWaypoint != "end")
    {
        found = false;
        for (const auto& i : waypointsList)
            if (currentWaypoint == i.getWaypointCode())
            {
                found = true;
                const Waypoint& previous = routeWaypoints.back();
                Waypoint current = i;
                current.setDistanceToPrevious(previous);
                routeWaypoints.push_back(current);
                break;
            }
        if (found == false)
        {
            std::cerr << "Invalid waypoint selected!\n";
            return;
        }
        std::cin >> currentWaypoint;
    }
    for (const auto& i : waypointsList)
        if (arrivalIcao == i.getWaypointCode())
        {
            const Waypoint& previous = routeWaypoints.back();
            Waypoint current = i;
            current.setDistanceToPrevious(previous);
            routeWaypoints.push_back(current);
            break;
        }
    //aircraft selection
    found = false;
    std::cout << "Aircraft type: ";
    std::string acType;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, acType);
    Aircraft ac;
    for (const auto& i : aircraftsList)
        if (acType == i.getType())
        {
            found = true;
            ac = i;
            break;
        }
    if (found == false)
    {
        std::cerr << "Invalid aircraft type!\n";
        return;
    }
    //cruising altitude selection
    std::cout << "Cruise altitude: ";
    std::string cruiseAlt;
    int cruiseAltInput = 0;
    std::cin >> cruiseAlt;
    if (cruiseAlt != "auto")
        cruiseAltInput = std::stoi(cruiseAlt);
    //PerformanceCalculation input data
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
    //PerformanceCalculation input data
    std::cout << "=======================\n";
    std::cout << "=== Payload entries ===\n";
    std::cout << "=======================\n";
    std::cout << "Freight: ";
    double freightInput;
    std::cin >> freightInput;
    std::cout << "Passengers: ";
    int passengersInput;
    std::cin >> passengersInput;
    std::cout << "\n=======================\n\n";
    PerformanceCalculation perfCalc{freightInput, passengersInput};
    Route rt1{cruiseAltInput, fltNumber, callSgn, depart, arrival,
        departRw, arrivalRw,
             routeWaypoints, ac, fuelPlanning, perfCalc};
    if (rt1.routeInit() == false)
    {
        std::cerr << "Invalid flight plan data!\n";
        return;
    }
    if (rt1.fuelManagementInit() == false)
    {
        std::cerr << "Invalid fuel data!\n";
        return;
    }
    if (rt1.performanceCalculationInit() == false)
    {
        std::cerr << "Invalid payload data!\n";
        return;
    }
    std::cout << rt1;
}