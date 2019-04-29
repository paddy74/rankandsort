#include <rankandsort/MasterRanker.hpp>

#include <lowletorfeats/base/utillf.hpp>
#include <textalyzer/utils.hpp>


namespace rankandsort
{

/* Public static class variables */

std::array<std::string, 2> const MasterRanker::RANKERS = {
    "tfidf", "bm25f"
};


/* Constructors */

MasterRanker::MasterRanker(
    std::string const & queryText,
    base::ResultPage fullResultPage
)
{
    this->queryText = queryText;
    this->resultPage = fullResultPage;

    // Calculate `queryTfMap`
    this->queryTfMap = textalyzer::asFrequencyMap(
        MasterRanker::analyzerFun(queryText, 2).first);

    // Construct the `querySentenceMatrix`
}


/* Public class methods */

void MasterRanker::rank()
{
    this->rankWith("tfidf", 50);
    this->rankWith("bm25f", 25);
}


void MasterRanker::rankWith(
    std::string const & rankerName, std::size_t const & upperSize)
{
    if (rankerName == "tfidf")
        this->rankTfidf(upperSize);
    else if (rankerName == "bm25f")
        this->rankBm25f(upperSize);
}


/* Private static member variables */

textalyzer::AnlyzerFunType<std::string> const MasterRanker::analyzerFun
    = textalyzer::Analyzer::medAnalyze;

}
