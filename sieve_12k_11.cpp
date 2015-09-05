#include "sieve_impl.hpp"
#include <functional>
#include <tuple>

namespace prime_counter {

eq_ans ans_3;

void init_sieve3() {
  ans_3 = solve_mod<3, -1, 12, 11, 10, 30>();
}

void sieve3_impl(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B,
    const int64_t f, const int64_t g) {
  int64_t x = f, y0 = g;
  int64_t k0 = 3*f*f-g*g;
  while (true) {
    while (k0 >= (int64_t)(L+B)) {
      if (x <= y0) break;
      k0 -= 60*y0 + 900;
      y0 += 30;
    } if (k0 >= (int64_t)(L+B) && x <= y0) break;
    int64_t k = k0, y = y0;
    while (k>=(int64_t)L && y<x) {
      bit_ary.flip(k-L);
      k -= 60*y + 900;
      y += 30;
    }
    k0 += 60*x+300;
    x += 10;
  }
}

void sieve3(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B) {
  sieve<>(bit_ary, L, B, ans_3, sieve3_impl);
}

}

