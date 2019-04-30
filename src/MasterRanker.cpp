#include <rankandsort/MasterRanker.hpp>

#include <textalyzer/utils.hpp>

#include <algorithm>


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
    /* Low FC */

    // Select the lowFC
    std::string fKeyStr;
    if (rankerName == "tfidf")
        fKeyStr = "tfidf.tfidf.full";
    else if (rankerName == "bm25f")
        fKeyStr = "okapi.bm25f.full";

    // Collect r-scores
    this->rankLow(upperSize, fKeyStr);

    // Sort by the r-score
    std::sort(this->resultPage.begin(), this->resultPage.end() + upperSize,
        MasterRanker::RscoreCompare());
}


/* Private static member variables */

textalyzer::AnlyzerFunType<std::string> const MasterRanker::analyzerFun
    = textalyzer::Analyzer::medAnalyze;

}
