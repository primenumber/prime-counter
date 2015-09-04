#include "sieve_impl.hpp"
#include <functional>
#include <tuple>

namespace prime_counter {

eq_ans ans_1;

void init_sieve1() {
  ans_1 = solve_mod<4, 1, 4, 1>();
}

void sieve1_impl(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B,
    const int64_t f, const int64_t g) {
  int64_t x = f, y0 = g;
  int64_t k0 = 4*f*f + g*g;
  while (k0 < (int64_t)(L+B)) {
    k0 += 480*x + 14400;
    x += 60;
  }
  while (true) {
    x -= 60;
    k0 -= 480*x + 14400;
    if (x <= 0) break;
    while (k0 < (int64_t)L) {
      k0 += 120*y0 + 3600;
      y0 += 60;
    }
    int64_t k = k0, y = y0;
    while (k < (int64_t)(L+B)) {
      bit_ary.flip(k-L);
      k += 120*y + 3600;
      y += 60;
    }
  }
}

void sieve1(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B) {
  sieve<>(bit_ary, L, B, ans_1, sieve1_impl);
}

}
