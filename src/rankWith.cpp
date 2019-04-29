#include <rankandsort/MasterRanker.hpp>

#include <lowletorfeats/FeatureCollector.hpp>
#include <lowletorfeats/base/FeatureKey.hpp>


namespace rankandsort
{

void MasterRanker::rankTfidf(std::size_t const & upperSize)
{
    base::ResultPage upperResultPage(
        this->resultPage.begin(), this->resultPage.end() + upperSize);
    lowletorfeats::FeatureCollector lowFC(upperResultPage, this->queryTfMap);

    lowFC.collectFeatures(
        lowletorfeats::base::FeatureKey("tfidf", "tfidf", "full"));
}


void MasterRanker::rankBm25f(std::size_t const & upperSize)
{
    base::ResultPage upperResultPage(
        this->resultPage.begin(), this->resultPage.end() + upperSize);
    lowletorfeats::FeatureCollector lowFC(upperResultPage, this->queryTfMap);

    lowFC.collectFeatures(
        lowletorfeats::base::FeatureKey("okapi", "bm25f", "full"));
}

}
