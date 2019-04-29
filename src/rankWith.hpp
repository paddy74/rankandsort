#pragma once

#include <rankandsort/MasterRanker.hpp>


namespace rankandsort
{

void rankTfidf(MasterRanker &, std::size_t const &);
void rankBm25f(MasterRanker &, std::size_t const &);

}
