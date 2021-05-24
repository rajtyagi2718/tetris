#ifndef FEATURES_H 
#define FEATURES_H 

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>

namespace features
{
using boost::multiprecision::uint256_t;

std::vector<double> values(uint256_t state, int pre_clears);

int get_clears(uint256_t& state);
int get_blocks(uint256_t& state);
}  // namespace features

namespace internal
{
using boost::multiprecision::uint256_t;

std::vector<int> get_heights(uint256_t state);
std::vector<int> get_abs_adjacent_difference(std::vector<int>& heights);
}  // namespace internal

#endif  // FEATURES_H 
