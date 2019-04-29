#include <rankandsort/MasterRanker.hpp>

#include <lowletorfeats/FeatureCollector.hpp>
#include <lowletorfeats/base/FeatureKey.hpp>

#include <cpp11-range/range.hpp>  // util::lang::indices


namespace rankandsort
{

void MasterRanker::rankLow(
    std::size_t const & upperSize,
    std::string const & fKeyStr)
{
    lowletorfeats::base::FeatureKey fKey(fKeyStr);

    // Create the lowFC from the upperSize range
    base::ResultPage upperResultPage(
        this->resultPage.begin(), this->resultPage.end() + upperSize);
    lowletorfeats::FeatureCollector lowFC(upperResultPage, this->queryTfMap);

    // Ensure the analyzer is set
    lowFC.setAnalyzerFunction(MasterRanker::analyzerFun);

    // Collect the features for the given key
    lowFC.collectFeatures(fKey);

    // Assign the r-scores
    auto const & lowFCDocs = lowFC.getDocVect();
    for (auto const & i : util::lang::indices(lowFCDocs))
        this->resultPage[i]["rscore"] = lowFCDocs[i].getFeatureValue(fKey);
}

}
