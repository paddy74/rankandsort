#include <iostream>
#include <rankandsort/rankandsort.hpp>

#include "testData.hpp"

int main()
{
    auto data = getTestData();

    std::cout << "Unsorted:" << std::endl;
    for (auto const & doc : data.second)
        {
            if (doc.count("id") == 0)
                std::cout << "noid" << ' ';
            else
                std::cout << doc.at("id") << ' ';
        }
    std::cout << std::endl;

    rankandsort::rankandsort(data.first, data.second);

    std::cout << "\nSorted:" << std::endl;
    for (auto const & doc : data.second)
        {
            if (doc.count("id") == 0)
                std::cout << "noid" << ' ';
            else
                std::cout << doc.at("id") << ' ';
        }
    std::cout << std::endl;

    return 0;
}
