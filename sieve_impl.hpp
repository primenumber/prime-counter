#pragma once
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include "bitarray.hpp"

namespace prime_counter {

using eq_ans = std::vector<std::tuple<int64_t, int64_t>>;
using bit_ary_t = bitarray;

void init_sieve1();
void init_sieve2();
void init_sieve3();
void sieve1(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B);
void sieve2(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B);
void sieve3(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B);

template <int64_t a, int64_t b, int64_t MOD, int64_t REM,
         int64_t xrange, int64_t yrange>
eq_ans solve_mod() {
  std::vector<int64_t> rems;
  for (int64_t i = 0; i < 60; ++i) {
    if ((i % 2) == 0 || (i % 3) == 0 || (i % 5) == 0) continue;
    if ((i % MOD) == REM) rems.push_back(i);
  }
  eq_ans res;
  for (int64_t x = 0; x < xrange; ++x) {
    for (int64_t y = 0; y < yrange; ++y) {
      int64_t k = (a*x*x + b*y*y + (abs(a) + abs(b)) * 3600) % 60;
      for (int64_t r : rems) {
        if (k == r) {
          res.emplace_back(x, y);
          break;
        }
      }
    }
  }
  return res;
}

template <typename Func>
void sieve(bit_ary_t &bit_ary, const uint64_t L, const uint64_t B, const eq_ans &ans, Func &func) {
  for (auto tp : ans) {
    int64_t f, g;
    std::tie(f, g) = tp;
    func(bit_ary, L, B, f, g);
  }
}

inline void init_sieve() {
  init_sieve1();
  init_sieve2();
  init_sieve3();
}

} // namespace prime_counter
