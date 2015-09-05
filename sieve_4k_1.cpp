#include "sieve_impl.hpp"
#include <functional>
#include <tuple>

namespace prime_counter {

eq_ans ans_1;

void init_sieve1() {
  ans_1 = solve_mod<4, 1, 4, 1, 15, 30>();
}

void sieve1_impl(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B,
    const int64_t f, const int64_t g) {
  int64_t x = f, y0 = g;
  int64_t k0 = 4*f*f + g*g;
  while (k0 < (int64_t)(L+B)) {
    k0 += 120*x + 900;
    x += 15;
  }
  while (true) {
    x -= 15;
    k0 -= 120*x + 900;
    if (x <= 0) break;
    while (k0 < (int64_t)L) {
      k0 += 60*y0 + 900;
      y0 += 30;
    }
    int64_t k = k0, y = y0;
    while (k < (int64_t)(L+B)) {
      bit_ary.flip(k-L);
      k += 60*y + 900;
      y += 30;
    }
  }
}

void sieve1(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B) {
  sieve<>(bit_ary, L, B, ans_1, sieve1_impl);
}

}
