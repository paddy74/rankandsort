#pragma once

#include <rankandsort/base/stdDef.hpp>

#include <textalyzer/Analyzer.hpp>
#include <lowletorfeats/FeatureCollector.hpp>

#include <string>
#include <unordered_map>


namespace rankandsort
{

/**
 * @brief Conducts an end-to-end ranking pipeline for a given set of documents
 *  and query text. This class conducts a multi-stage ranking process.
 *
 */
class MasterRanker
{
public:
    /* Constructors */

    MasterRanker(
        std::string const & queryText,
        base::ResultPage fullResultPage
    );


    /* Public class methods */

    // Rank and sort the results using the preset multi-stage ranking process
    void rank();

    // Rank and sort only using the given ranker
    void rankWith(
        std::string const & rankerName, std::size_t const & upperSize);


    /* Public getters */

    std::vector<std::string> getAvailableRankers() const;

private:
    /* Private member variables */

    std::string queryText;
    base::ResultPage resultPage;

    lowletorfeats::FeatureCollector lowFC;
    //highletorfeats::FeatureCollector highFC;


    /* Private static member variables */

    textalyzer::AnlyzerFunType<std::string> static const analyzerFun;

    std::unordered_map<
        std::string,
        std::function<void(MasterRanker &, std::size_t const &)>
    > static const RANKER_MAP;


    /* Private class methods */

    void initLowFC();
    void initHighFC();
};

}
