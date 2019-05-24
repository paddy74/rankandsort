#include <rankandsort/rankandsort.hpp>

#include "testData.hpp"


int main()
{
    auto data = getTestData();
    auto const & queryString = data.first;
    auto & docVect = data.second;

    rankandsort::rankandsort(queryString, docVect);

    return 0;
}
