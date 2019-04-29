#pragma once

#include <rankandsort/base/stdDef.hpp>

#include <textalyzer/Analyzer.hpp>
#include <lowletorfeats/base/stdllf.hpp>

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
    /* Public static class variables */

    std::array<std::string, 2> static const RANKERS;


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

private:
    /* Private member variables */

    std::string queryText;
    lowletorfeats::base::StrUintMap queryTfMap;
    base::SentenceMatrix querySentenceMatrix;

    base::ResultPage resultPage;


    /* Private static member variables */

    textalyzer::AnlyzerFunType<std::string> static const analyzerFun;


    /* Private class methods */

    void rankLow(std::size_t const & upperSize, std::string const & fKeyStr);


    /* Private class structures */

    struct RscoreCompare
    {
        inline bool operator() (
            base::DocData const & a, base::DocData const & b)
        { return (a.at("rscore") < b.at("rscore")); }
    };
};

}
