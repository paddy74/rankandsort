#include <algorithm>
#include <cpp11-range/range.hpp>  // util::lang::indices
#include <lowletorfeats/FeatureCollector.hpp>
#include <lowletorfeats/base/FeatureKey.hpp>
#include <rankandsort/MasterRanker.hpp>
#include <textalyzer/utils.hpp>

namespace rankandsort
{
/* Public static class variables */

/**
 * @brief String names of the supported ranking methods.
 *
 */
std::array<std::string, 2> const MasterRanker::RANKERS = {"tfidf", "bm25f"};

/* Constructors */

/**
 * @brief Construct a new instance empty MasterRanker.
 *
 */
MasterRanker::MasterRanker()  // TODO: Fully define
{
    this->queryText = "";
}

/**
 * @brief Construct a new Master Ranker using the default constructor.
 *
 * @param queryText String representation of the query.
 * @param fullResultPage Preanalyzed result page in the following format:
 *  {
 *      "id": string,
 *      "rscore": float,
 *      # Necessary for HighFC
 *      "sentence_matrix": [
 *          [string, ..., string],
 *          ...,
 *          [string, ..., string]
 *      ],
 *      # Necessary for LowFC
 *      "url_tokens": [string, ..., string],
 *      "title_tokens": [string, ..., string],
 *      "author_tokens": [string, ..., string],
 *      "anchor_tokens": [string, ..., string],
 *      "body_tokens": [string, ..., string]
 *  }
 */
MasterRanker::MasterRanker(
    std::string const & queryText, base::ResultPage const & fullResultPage)
{
    this->queryText = queryText;
    this->resultPage = fullResultPage;

    // Calculate `queryTfMap`
    this->queryTfMap = textalyzer::asFrequencyMap(
        MasterRanker::analyzerFun(queryText, 2).first);
}

/**
 * @brief Copy constructor.
 *
 * @param other
 */
MasterRanker::MasterRanker(MasterRanker const & other)
{
    this->queryText = other.queryText;
    this->queryTfMap = other.queryTfMap;
    this->resultPage = other.resultPage;
}

/* Public class methods */

/**
 * @brief Rank and sort the result page using the preset multi-stage ranking
 *  process.
 *  Stage 0: Documents expected to be presorted using a static pointwise
 * method. Stage 1: Rank and sort top 50 documents with TF/IDF. Stage 2: Rank
 * and sort top 25 documents with BM25F. Stage 3: Rank and sort top 10
 * documents with a machine learned model.
 *
 */
void MasterRanker::defaultRankandsort()
{
    std::cerr << this << " MasterRanker::MasterRanker" << std::endl;
    std::cerr << &MasterRanker::analyzerFun << " MasterRanker::analyzerFun"
              << std::endl;
    std::cerr << &MasterRanker::RANKERS << " MasterRanker::RANKERS"
              << std::endl;
    this->rankandsortWith("tfidf", 50);
    // this->rankandsortWith("bm25f", 25);
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
    // Handle upperSize that is too large or 0
    if (upperSize > this->resultPage.size() || upperSize == 0)
        upperSize = resultPage.size();  // To large or 0, set to .end()

    /* Low FC */  // TODO: Handle High FC

    // Select the lowFC
    std::string fKeyStr;
    if (rankerName == "tfidf")
        fKeyStr = "tfidf.tfidf.full";
    else if (rankerName == "bm25f")
        fKeyStr = "okapi.bm25f.full";
    else
        return;  // Do nothing - break from function, not supported.

    // Calculate r-scores in each document
    this->calcLowRscores(fKeyStr, upperSize);
    std::cerr << "MasterRanker::rankandsortWith" << std::endl;
    // Sort the result page by the r-score
    std::sort(
        this->resultPage.begin(), this->resultPage.begin() + upperSize,
        MasterRanker::RscoreCompare());
}

/* Public static methods */

/**
 * @brief Set the `MasterRanker::analyzerFun` private static variable.
 *
 * @param analyzerFunction
 */
void MasterRanker::setAnalyzerFunction(
    textalyzer::AnlyzerFunType<std::string> const & analyzerFunction)
{
    MasterRanker::analyzerFun = analyzerFunction;
}

/* Private static member variables */

/**
 * @brief The default analyzer function to be used.
 *
 */
textalyzer::AnlyzerFunType<std::string> MasterRanker::analyzerFun =
    textalyzer::Analyzer::medAnalyze;

/* Private class methods */

void MasterRanker::calcLowRscores(
    std::string const & fKeyStr, std::size_t upperSize)
{
    // Handle upperSize that is too large
    if (upperSize > this->resultPage.size())
        upperSize = resultPage.size();  // To large, set to .end()

    // Create the lowFC from the upperSize range
    base::ResultPage upperResultPage(  // TODO: View not copy
        this->resultPage.begin(), this->resultPage.begin() + upperSize);

    std::cerr << &upperResultPage << " upperResultPage" << std::endl;
    std::cerr << &this->resultPage[0] << " this->resultPage[0]" << std::endl;
    std::cerr << &upperResultPage[0] << " upperResultPage[0]" << std::endl;

    lowletorfeats::FeatureCollector lowFC(upperResultPage, this->queryTfMap);
    std::cerr << "PASS: MasterRanker::analyzerFun" << std::endl;
    // Set the analyzer of lowFC
    lowFC.setAnalyzerFunction(MasterRanker::analyzerFun);

    // Collect the features for the given key
    lowletorfeats::base::FeatureKey fKey(fKeyStr);
    lowFC.collectFeatures(fKey);  // TODO: String overload

    // Assign the r-scores
    auto const & lowFCDocs = lowFC.getDocVect();
    for (auto const & i : util::lang::indices(lowFCDocs))
        this->resultPage[i]["rscore"] = lowFCDocs[i].getFeatureValue(fKey);
}

}  // namespace rankandsort
