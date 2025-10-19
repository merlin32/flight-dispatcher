#include <iostream>
#include "header/Airport.h"

int main() {
    Runway rw1("08L", 3500, Wet, true);
    Runway rw2("08R", 3501, Wet, true);
    std::vector<Runway> airportRunways = {rw1, rw2};
    Weather wh1("20/10/2025 14:00", "20/10/2025 23:59", "LROP 191900Z 08005KT CAVOK 08/M00 Q1021 NOSIG");
    Airport ap1("Aeroportul International Henri Coanda", "LROP", "OTP", 26.1034, 44.5721, airportRunways, wh1);
    std::cout << ap1;

    return 0;
}
