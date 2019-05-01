#pragma once

#include <rankandsort/base/stdDef.hpp>

#include <textalyzer/Analyzer.hpp>
#include <lowletorfeats/base/stdDef.hpp>

#include <string>
#include <unordered_map>
#include <iostream>

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
    void defaultRankandsort();

    // Rank and sort using only the given ranker
    void rankandsortWith(
        std::string const & rankerName, std::size_t upperSize);

private:
    /* Private member variables */

    std::string queryText;
    lowletorfeats::base::StrUintMap queryTfMap;
    base::SentenceMatrix querySentenceMatrix;

    base::ResultPage resultPage;


    /* Private static member variables */

    textalyzer::AnlyzerFunType<std::string> static const analyzerFun;


    /* Private class methods */

    void rankLow(std::string const & fKeyStr, std::size_t upperSize);


    /* Private class structures */

    /**
     * @brief Compare two `DocData` instances using their r-score.
     *
     */
    struct RscoreCompare
    {
        inline bool operator() (
            base::DocData const & a, base::DocData const & b)
        {
            return (a.at("rscore") < b.at("rscore"));
        }
    };
};

}
