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
void rankandsort(
    std::string const & queryText,
    base::ResultPage & resultPage
);

}
