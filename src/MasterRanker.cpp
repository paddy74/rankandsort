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

/**
 * @brief Rank and sort the result page using the preset multi-stage ranking
 *  process.
 *  Stage 0: Documents expected to be presorted using a static pointwise method.
 *  Stage 1: Rank and sort top 50 documents with TF/IDF.
 *  Stage 2: Rank and sort top 25 documents with BM25F.
 *  Stage 3: Rank and sort top 10 documents with a machine learned model.
 *
 */
void MasterRanker::defaultRankandsort()
{
    this->rankandsortWith("tfidf", 50);
    this->rankandsortWith("bm25f", 25);
}


/**
 * @brief Rank and sort using the named ranker. If the rankerName is not found
 *  in `MasterRanker::RANKERS` then do nothing.
 *
 * @param rankerName
 * @param upperSize
 */
void MasterRanker::rankandsortWith(
    std::string const & rankerName, std::size_t upperSize)
{
    // Handle upperSize that is too large
    if (upperSize > this->resultPage.size())
        upperSize = resultPage.size();  // To large, set to .end()

    /* Low FC */

    // Select the lowFC
    std::string fKeyStr;
    if (rankerName == "tfidf")
        fKeyStr = "tfidf.tfidf.full";
    else if (rankerName == "bm25f")
        fKeyStr = "okapi.bm25f.full";
    else return;  // Do nothing - break from function, not supported.

    // Calculate r-scores in each document
    this->rankLow(fKeyStr, upperSize);

    // Sort the result page by the r-score
    std::sort(this->resultPage.begin(), this->resultPage.begin() + upperSize,
        MasterRanker::RscoreCompare());
}


/* Private static member variables */

textalyzer::AnlyzerFunType<std::string> const MasterRanker::analyzerFun
    = textalyzer::Analyzer::medAnalyze;

}
