#include <rankandsort/MasterRanker.hpp>
#include <rankandsort/rankandsort.hpp>

namespace rankandsort
{
void rankandsort(std::string const & queryText, base::ResultPage & resultPage)
{
    MasterRanker ranker(queryText, resultPage);
    ranker.defaultRankandsort();
}

void rankandsort(
    std::string const & queryText, base::ResultPage & resultPage,
    std::string const & rankerName, std::size_t const & upperSize)
{
    MasterRanker ranker(queryText, resultPage);
    ranker.rankandsortWith(rankerName, upperSize);
}

std::array<std::string, 2> const & getAvailableRankers()
{
    return MasterRanker::RANKERS;
}

}  // namespace rankandsort
