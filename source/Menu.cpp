#include "../header/Menu.h"

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
void Menu::menuStart()
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
    for (const auto& i:aircraftsList)
        std::cout << i;
    for (const auto& i:airportsList)
        std::cout << i;
    for (const auto& i:waypointsList)
        std::cout << i;
}