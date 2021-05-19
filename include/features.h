#ifndef FEATURES_H 
#define FEATURES_H 

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>

namespace features
{
using boost::multiprecision::uint256_t;

std::vector<double> values(uint256_t state, int pre_clears);

int clears(uint256_t state);
int height(uint256_t state);
int bumps(uint256_t state);
int holes(uint256_t state);
}  // namespace features

namespace internal
{
using boost::multiprecision::uint256_t;

std::vector<int> getheights(uint256_t state);
}  // namespace internal

#endif  // FEATURES_H 
