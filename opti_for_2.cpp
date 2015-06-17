#include <cmath>
#include "prime_counter.hpp"

namespace prime_counter {

result::result opti_for_2(const uint64_t n) {
  std::vector<bool> is_prime((n+1)/2, true);
  is_prime[0] = false;
  uint64_t sqrt_n = sqrt(n+0.5);
  for (uint64_t i = 1; i*2+1 <= sqrt_n; ++i)
    if (is_prime[i])
      for (uint64_t j = 2*i*(i+1); j*2+1 <= n; j += 2*i+1)
        is_prime[j] = false;
  result::result res(n, sqrt_n);
  if (n >= 2) res.count[1/sqrt_n] += 1;
  for (uint64_t i = 0; i*2+1 <= n; ++i)
    res.count[(i*2)/sqrt_n] += is_prime[i];
  return res;
}

} // namespace prime_counter
