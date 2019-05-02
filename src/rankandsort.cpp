#include <rankandsort/MasterRanker.hpp>
#include <rankandsort/rankandsort.hpp>

namespace rankandsort
{
void rankandsort(std::string const & queryText, base::ResultPage & resultPage)
{
    MasterRanker ranker(queryText, resultPage);
    ranker.defaultRankandsort();
}

}  // namespace rankandsort
