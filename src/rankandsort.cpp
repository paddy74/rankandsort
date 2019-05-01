#include <rankandsort/rankandsort.hpp>

#include <rankandsort/MasterRanker.hpp>


namespace rankandsort
{

void rankandsort(
    std::string const & queryText,
    base::ResultPage & resultPage
)
{
    MasterRanker ranker(queryText, resultPage);
    ranker.defaultRankandsort();
}

}
