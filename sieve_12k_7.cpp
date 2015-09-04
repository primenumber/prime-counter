#include "sieve_impl.hpp"
#include <functional>
#include <tuple>

namespace prime_counter {

eq_ans ans_2;

void init_sieve2() {
  ans_2 = solve_mod<3, 1, 12, 7>();
}

void sieve2_impl(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B,
    const int64_t f, const int64_t g) {
  int64_t x = f, y0 = g;
  int64_t k0 = 3*f*f+g*g;
  while (k0 < (int64_t)(L+B)) {
    k0 += 360*x + 10800;
    x += 60;
  }
  while (true) {
    x -= 60;
    k0 -= 360*x + 10800;
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

void sieve2(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B) {
  sieve<>(bit_ary, L, B, ans_2, sieve2_impl);
}

}

