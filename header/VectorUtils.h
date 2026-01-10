
#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include <vector>
#include <string>

template <typename T>
void sortClassArray(std::vector<T>& unsortedArray);
template <typename T>
bool compareClassElements(const T& t1, const T& t2);
template <typename T>
bool hasDigitsOnly(const T &container, const bool& isDouble);
template <typename T>
void validInputItem(const std::string& message, T& parameter);
template <typename T>
void validInputVector(const std::string& message, std::vector<T>& parameter, const int& size);


#endif //VECTORUTILS_H
