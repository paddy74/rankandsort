#include <rankandsort/MasterRanker.hpp>

#include <lowletorfeats/FeatureCollector.hpp>
#include <lowletorfeats/base/FeatureKey.hpp>

#include <cpp11-range/range.hpp>  // util::lang::indices


namespace rankandsort
{

void MasterRanker::rankLow(
    std::string const & fKeyStr, std::size_t upperSize)
{
    // Handle upperSize that is too large
    if (upperSize > this->resultPage.size())
        upperSize = resultPage.size();  // To large, set to .end()

    lowletorfeats::base::FeatureKey fKey(fKeyStr);

    // Create the lowFC from the upperSize range
    base::ResultPage upperResultPage(
        this->resultPage.begin(), this->resultPage.begin() + upperSize);
    lowletorfeats::FeatureCollector lowFC(upperResultPage, this->queryTfMap);

    // Set the analyzer of lowFC
    lowFC.setAnalyzerFunction(MasterRanker::analyzerFun);

    // Collect the features for the given key
    lowFC.collectFeatures(fKey);

    // Assign the r-scores
    auto const & lowFCDocs = lowFC.getDocVect();
    for (auto const & i : util::lang::indices(lowFCDocs))
        this->resultPage[i]["rscore"] = lowFCDocs[i].getFeatureValue(fKey);
}

}
