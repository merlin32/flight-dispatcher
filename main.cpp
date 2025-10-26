#include "header/Airport.h"
#include "header/Aircraft.h"
#include "header/Waypoint.h"

int main() {
    Runway rw1("08L", 3500, Wet, true);
    Runway rw2("08R", 3501, Wet, true);
    std::vector<Runway> airportRunways = {rw1, rw2};
    Weather wh1("20/10/2025 14:00", "20/10/2025 23:59", "LROP 191900Z 08005KT CAVOK 08/M00 Q1021 NOSIG");
    Airport ap1("Aeroportul International Henri Coanda", "LROP", "OTP", 26.1034, 44.5721, airportRunways, wh1);
    std::cout << ap1;
    unsigned int rwPos = ap1.getLongestRunway();
    std::cout << "Longest runway: \n" << ap1.getRunway(rwPos);
    Aircraft ac1(100, 210.145, 12045.1, 125, 50,
        10, 1, 6816, 1925, 1251,
        1205412, 12051, 12501, 5751, 1258, "YR-FSA");
    std::cout << ac1 << '\n';
    Waypoint wp1("POLUN", 44.237978, 25.223372, 0, 0, false);
    std::cout << wp1 << '\n';
    return 0;
}
