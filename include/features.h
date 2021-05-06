#ifndef FEATURES_H 
#define FEATURES_H 

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>  // vector

namespace features
{
using boost::multiprecision::uint256_t;

std::vector<double> values(uint256_t boardint);

int clears(uint256_t boardint);
int height(uint256_t boardint);
int bumps(uint256_t boardint);
int holes(uint256_t boardint);
}  // namespace features

namespace internal
{
using boost::multiprecision::uint256_t;

std::vector<int> getheights(uint256_t boardint);
}  // namespace internal

#endif  // FEATURES_H 
