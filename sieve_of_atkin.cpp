#include "prime_counter.hpp"
#include <cmath>

namespace prime_counter {

result::result sieve_of_atkin(const uint64_t n) {
  std::vector<bool> is_prime(n+1, false);
  uint64_t sqn = sqrt(n+0.5);
  uint64_t b;
  for (uint64_t z = 1; z <= 5; z += 4) {
    for (uint64_t y = z; y <= sqn; y += 6) {
      for (uint64_t x = 1; x <= sqn && (b = 4*x*x + y*y) <= n; ++x)
        is_prime[b] = !is_prime[b];
      for (uint64_t x = y+1; x <= sqn && (b = 3*x*x - y*y) <= n; x += 2)
        is_prime[b] = !is_prime[b];
    }
  }
  for (uint64_t z = 2; z <= 4; z += 2) {
    for (uint64_t y = z; y <= sqn; y += 6) {
      for (uint64_t x = 1; x <= sqn && (b = 3*x*x + y*y) <= n; x += 2)
        is_prime[b] = !is_prime[b];
      for (uint64_t x = y+1; x <= sqn && (b = 3*x*x - y*y) <= n; x += 2)
        is_prime[b] = !is_prime[b];
    }
  }
  for (uint64_t y = 3; y <= sqn; y += 6) {
    for (uint64_t z = 1; z <= 2; ++z) {
      for (uint64_t x = z; x <= sqn && (b = 4*x*x + y*y) <= n; x += 3)
        is_prime[b] = !is_prime[b];
    }
  }
  for (uint64_t i = 5; i <= sqn; i += 2)
    if (is_prime[i])
      for (uint64_t j = i*i; j <= n; j += i*i)
        is_prime[j] = false;
  is_prime[2] = is_prime[3] = true;
  result::result res(n, sqn);
  for (uint64_t i = 1; i <= n; ++i)
    res.count[(i-1)/sqn] += is_prime[i];
  return res;
}

} // namespace prime_counter
