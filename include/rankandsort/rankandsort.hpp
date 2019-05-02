#pragma once

#include <rankandsort/base/stdDef.hpp>

namespace rankandsort
{
/**
 * @brief Conduct end-to-end ranking and sorting using the default methods.
 *
 * @param queryText String representation of the query.
 * @param resultPage An ordered list of `base::DocType`.
 */
void rankandsort(std::string const & queryText, base::ResultPage & resultPage);

/**
 * @brief Conduct ranking and sorting using the named method.
 *
 * @param queryText
 * @param resultPage
 * @param rankerName
 * @param upperSize
 */
void rankandsort(
    std::string const & queryText, base::ResultPage & resultPage,
    std::string const & rankerName, std::size_t const & upperSize);

/**
 * @brief Get an array of the rankers that are available.
 *
 * @return std::array<std::string, 2> const&
 */
std::array<std::string, 2> const & getAvailableRankers();

}  // namespace rankandsort
