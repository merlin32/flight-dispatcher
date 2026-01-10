#include "../header/VectorUtils.h"
#include "../header/Exceptions.h"
#include <algorithm>
#include <string>
#include <iostream>

template <typename T>
bool compareClassElements(const T& t1, const T& t2)
{
    return t1 < t2;
}
template <typename T>
void sortClassArray(std::vector<T>& unsortedArray)
{
    std::sort(unsortedArray.begin(), unsortedArray.end(), compareClassElements<T>);
}
template <typename T>
bool hasDigitsOnly(const T& container, const bool& isDouble)
{
    if (container.empty()) return false;
    if (isDouble && std::count(container.begin(), container.end(), '.') > 1) {
        return false;
    }
    T copy = container;
    if (isDouble == false)
        copy.erase(std::remove_if(copy.begin(), copy.end(), [](unsigned char c)
            {
                return !std::isdigit(c);
            }), copy.end());
    else
        copy.erase(std::remove_if(copy.begin(), copy.end(), [](unsigned char c)
            {
                return !std::isdigit(c) && c != '.';
            }), copy.end());
    if (!copy.empty())
        return copy == container;
    return false;
}
template <typename T>
void validInputItem(const std::string& message, T& parameter)
{
    std::string inputValue;
    while (true)
    {
        try
        {
            std::cout << message;
            std::getline(std::cin, inputValue);
            //checking the type for T
            if constexpr (std::is_same_v<T, int>)
                if (hasDigitsOnly<std::string>(inputValue, false) == true)
                {
                    parameter = std::stoi(inputValue);
                    break;
                }
            if constexpr (std::is_same_v<T, double>)
                if (hasDigitsOnly<std::string>(inputValue, true) == true)
                {
                    parameter = std::stod(inputValue);
                    break;
                }
            throw AppException("Invalid input! Try again!");
        }
        catch (const AppException& err)
        {
            std::cerr << err.what() << '\n';
        }
        catch (const std::exception& err)
        {
            std::cerr << "stoi: " << err.what() << '\n';
        }
    }
}
template <typename T>
void validInputVector(const std::string& message, std::vector<T>& parameter, const int& size)
{
    for (int i = 0; i < size;)
    {
        try
        {
            std::string inputValue;
            std::cout << message << i + 1 << ": ";
            std::getline(std::cin, inputValue);
            T temp;
            if constexpr (std::is_same_v<T, double>)
            {
                if (hasDigitsOnly<std::string>(inputValue, true) == true)
                    temp = std::stod(inputValue);
                else
                    throw AppException("Invalid input! Try again!");
            }
            else
                throw AppException("Invalid input! Try again!");
            parameter.push_back(temp);
            i++;
        }
        catch (const AppException& err)
        {
            std::cerr << err.what() << '\n';
        }
        catch (const std::exception& err)
        {
            std::cerr << "stoi: " << err.what() << '\n';
        }
    }
}