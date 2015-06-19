#pragma once
#include "result.hpp"

namespace prime_counter {

result::result naive(const uint64_t n);
result::result opti_for_2(const uint64_t n);
result::result sieve_of_atkin(const uint64_t n);
result::result sieve_of_atkin_interval(const uint64_t n);
std::vector<uint64_t> prime_list(const uint64_t n);

}
