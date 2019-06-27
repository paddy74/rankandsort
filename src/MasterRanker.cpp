#include <algorithm>
#include <cpp11-range/range.hpp>  // util::lang::indices
#include <lowletorfeats/FeatureCollector.hpp>
#include <lowletorfeats/base/FeatureKey.hpp>
#include <rankandsort/MasterRanker.hpp>
#include <textalyzer/utils.hpp>

#include "models/lowHighModel.h"

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
    std::string const & queryText, base::ResultPage & fullResultPage)
    : resultPage(fullResultPage)
{
    this->queryText = queryText;

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
    : resultPage(other.resultPage)
{
    this->queryText = other.queryText;
    this->queryTfMap = other.queryTfMap;
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
    this->rankandsortWith("tfidf", 50);
    this->rankandsortWith("bm25f", 25);
    this->rankandsortWith("lowhigh", 10);
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

    // If not in lowFC rankers
    if (rankerName == "lowhigh")
    {
        this->calcDTreeRscores(FeatureLevel::low, upperSize);
    }
    else if (rankerName == "highhigh")
    {
        MasterRanker::throwUnsupportedRanker(rankerName);
    }
    else
    {
        // Select the lowFC
        lowletorfeats::base::FeatureKey fKey;
        if (rankerName == "tfidf")
            fKey = lowletorfeats::base::FeatureKey("tfidf", "tfidf", "full");
        else if (rankerName == "bm25f")
            fKey = lowletorfeats::base::FeatureKey("okapi", "bm25f", "full");
        else
            MasterRanker::throwUnsupportedRanker(rankerName);

        // Calculate r-scores in each document
        this->calcLowRscores(fKey, upperSize);
    }

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

/**
 * @brief Get a view of the resultPage from 0 to upperSize.
 *  // TODO: View of values instead of copy.
 *
 * @param upperSize
 * @return base::ResultPage
 */
base::ResultPage MasterRanker::getUpperRpage(std::size_t & upperSize)
{
    // Handle upperSize that is too large
    if (upperSize > this->resultPage.size())
        upperSize = resultPage.size();  // To large, set to .end()

    // Create the upperResultPage from the upperSize range
    base::ResultPage upperResultPage(
        this->resultPage.begin(), this->resultPage.begin() + upperSize);

    return upperResultPage;
}

/**
 * @brief Rank and sort using a decision tree ensemble model created with
 *  Treelite and using the indicated level of features.
 *
 * @param featureLevel
 * @param upperSize
 */
void MasterRanker::calcDTreeRscores(
    FeatureLevel const & featureLevel, std::size_t upperSize)
{
    if (featureLevel == FeatureLevel::low)
    {
        // Calculate feature vector per document into the model's input format
        std::vector<Entry *> docEntriesVect;
        {
            // Calculate the feature vector per document
            std::vector<std::vector<lowletorfeats::base::FValType>>
                featureVects;
            {
                // Create the lowFC from the upperSize range
                base::ResultPage upperResultPage =
                    this->getUpperRpage(upperSize);
                lowletorfeats::FeatureCollector lowFC(
                    upperResultPage, this->queryTfMap);
                lowFC.setAnalyzerFunction(MasterRanker::analyzerFun);

                // Collect the feature set
                lowFC.collectPresetFeatures();
                featureVects = lowFC.getFeatureVects();
            }

            // Construct the usable feature vector
            for (auto const & docFeats : featureVects)
            {
                Entry * docEntryArr = new Entry[docFeats.size()];

                for (auto const & i : util::lang::indices(docFeats))
                    docEntryArr[i].fvalue = (float)docFeats.at(i);
                Entry * docEntryPtr = docEntryArr;
                docEntriesVect.push_back(docEntryPtr);

                delete[] docEntryArr;
            }
        }

        // Predict query relevance and assign the r-scores
        for (auto const & i : util::lang::indices(this->resultPage))
        {
            Entry * docEntry = docEntriesVect.at(i);
            int margin = 5;
            float const relevanceProb = predict(docEntry, margin);
            this->resultPage.at(i)["rscore"] = std::to_string(relevanceProb);
        }
    }
    else  // featureLevel == FeatureLevel::high
    {
        MasterRanker::throwUnsupportedRanker("highhigh");
    }
}

void MasterRanker::calcLowRscores(
    lowletorfeats::base::FeatureKey const & fKey, std::size_t upperSize)
{
    // Create the lowFC from the upperSize range
    base::ResultPage upperResultPage = this->getUpperRpage(upperSize);
    lowletorfeats::FeatureCollector lowFC(upperResultPage, this->queryTfMap);
    lowFC.setAnalyzerFunction(MasterRanker::analyzerFun);

    // Collect the features for the given key
    lowFC.collectFeatures(fKey);

    // Assign the r-scores
    auto const & lowFCDocs = lowFC.getDocVect();
    for (auto const & i : util::lang::indices(lowFCDocs))
    {
        this->resultPage[i]["rscore"] =
            std::to_string(lowFCDocs[i].getFeatureValue(fKey));
    }
}

/* Private static class methods */

void MasterRanker::throwUnsupportedRanker(std::string const & rankerName)
{
    throw std::runtime_error("Unsupported ranker name '" + rankerName + "'");
}

}  // namespace rankandsort
