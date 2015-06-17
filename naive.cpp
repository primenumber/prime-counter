#include <cmath>
#include "prime_counter.hpp"

namespace prime_counter {

result::result naive(const uint64_t n) {
  std::vector<bool> is_prime(n+1, true);
  is_prime[0] = is_prime[1] = false;
  uint64_t sqrt_n = sqrt(n+1);
  for (uint64_t i = 2; i <= sqrt_n; ++i)
    if (is_prime[i])
      for (uint64_t j = i*i; j <= n; j += i)
        is_prime[j] = false;
  result::result res(n, sqrt_n);
  for (uint64_t i = 1; i <= n; ++i)
    res.count[(i-1)/sqrt_n] += is_prime[i];
  return res;
}

} // namespace prime_counter 
