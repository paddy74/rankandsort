#include <iostream>
#include <rankandsort/rankandsort.hpp>

#include "testData.hpp"

int main()
{
    auto data = getTestData();
    auto const & queryString = data.first;
    auto & docVect = data.second;

    std::cout << "Unsorted:" << std::endl;
    for (auto const & doc : docVect)
    {
        if (doc.count("id") == 0)
            std::cout << "noid" << ' ';
        else
            std::cout << doc.at("id") << ':' << doc.at("rscore") << ' ';
    }
    std::cout << std::endl;

    rankandsort::rankandsort(queryString, docVect);

    std::cout << "\nSorted:" << std::endl;
    for (auto const & doc : docVect)
    {
        if (doc.count("id") == 0)
            std::cout << "noid" << ' ';
        else
            std::cout << doc.at("id") << ':' << doc.at("rscore") << ' ';
    }
    std::cout << std::endl;

    return 0;
}
