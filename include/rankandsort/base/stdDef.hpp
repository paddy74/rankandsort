#pragma once

#include <vector>
#include <unordered_map>


namespace rankandsort::base
{

typedef std::unordered_map<std::string, std::string> DocData;  // will be JSON
typedef std::vector<DocData> ResultPage;

}
