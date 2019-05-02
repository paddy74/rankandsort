#pragma once

#include <unordered_map>
#include <vector>

namespace rankandsort::base
{
typedef std::unordered_map<std::string, std::string> DocData;  // will be JSON
typedef std::vector<DocData> ResultPage;

typedef std::vector<std::vector<std::string>> SentenceMatrix;

}  // namespace rankandsort::base
