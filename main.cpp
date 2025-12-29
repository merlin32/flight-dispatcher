#include "header/Menu.h"
#include "header/Exceptions.h"

int main() {
    try
    {
        Menu flightDispatcher;
        flightDispatcher.initLocalData();
        while (true)
            flightDispatcher.mainMenu();
    }
    catch (const InvalidFile& err)
    {
        std::cerr << "Invalid file: " << err.what() << '\n';
    }
    catch (const JsonFaultyRead& err)
    {
        std::cerr << "Json: " << err.what() << '\n';
    }
    catch (const InvalidObjectCreation& err)
    {
        std::cerr << "Error creating object: " << err.what() << '\n';
    }
    catch (const AppException& err)
    {
        std::cerr << "App error: " << err.what() << '\n';
    }
    catch (const std::exception& err)
    {
        std::cerr << "Error occurred: " << err.what() << '\n';
    }
    return 0;
}

