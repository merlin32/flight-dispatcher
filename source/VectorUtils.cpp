#include "../header/VectorUtils.h"
#include <algorithm>

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
