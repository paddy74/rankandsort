#include <rankandsort/MasterRanker.hpp>

#include "rankWith.hpp"

#include <lowletorfeats/base/utillf.hpp>


namespace rankandsort
{

/* Constructors */

MasterRanker::MasterRanker(
    std::string const & queryText,
    base::ResultPage fullResultPage
)
{
    this->queryText = queryText;
    this->resultPage = fullResultPage;

    // Construct the low-level feature collector
    this->initLowFC();
}


/* Public class methods */

void MasterRanker::rank()
{
    auto const stage1 = MasterRanker::RANKER_MAP.at("tfidf");
    auto const stage2 = MasterRanker::RANKER_MAP.at("bm25f");

    stage1(*this, 50);
    stage2(*this, 25);
}


void MasterRanker::rankWith(
    std::string const & rankerName, std::size_t const & upperSize)
{
    auto const ranker = MasterRanker::RANKER_MAP.at(rankerName);
    ranker(*this, upperSize);
}


/* Public getters */

std::vector<std::string> MasterRanker::getAvailableRankers() const
{
    return lowletorfeats::base::Utillf::getKeyVect(
        MasterRanker::RANKER_MAP);
}


/* Private static member variables */

textalyzer::AnlyzerFunType<std::string> const MasterRanker::analyzerFun
    = textalyzer::Analyzer::medAnalyze;


std::unordered_map<
    std::string,
    std::function<void(MasterRanker &, std::size_t const &)>
> const RANKER_MAP =
{
    { "tfidf", rankTfidf},
    { "bm25f", rankBm25f}
};


/* Private class methods */

void MasterRanker::initLowFC()
{
    lowletorfeats::FeatureCollector::setAnalyzerFunction(this->analyzerFun);
    lowFC = lowletorfeats::FeatureCollector(this->resultPage, this->queryText);
}

}
