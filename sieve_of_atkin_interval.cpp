#include "prime_counter.hpp"
#include <cmath>
#include <algorithm>
#include <functional>
#include <tuple>
#include <vector>

namespace prime_counter {

using eq_ans = std::vector<std::tuple<int64_t, int64_t>>;

// solve ax^2 + by^2 = k (mod m), k = REM (mod MOD)
// required condition: m = 0 (mod MOD)
template <int64_t a, int64_t b, int64_t m, int64_t MOD, int64_t REM>
eq_ans solve_mod() {
  eq_ans res;
  for (int64_t x = 0; x < m; ++x) {
    for (int64_t y = 0; y < m; ++y) {
      int64_t k = a*x*x + b*y*y + (a+b)*m*m;
      if (k % MOD == REM) {
        res.emplace_back(x, y);
      }
    }
  }
  return res;
}

eq_ans solve_mod1() {
  std::array<int64_t, 8> rems = {1, 13, 17, 29, 37, 41, 49, 53};
  eq_ans res;
  for (int64_t x = 0; x < 60; ++x) {
    for (int64_t y = 0; y < 60; ++y) {
      int64_t k = 4*x*x + y*y;
      bool ok = false;
      for (int64_t r : rems) {
        if (k % 60 == r) {
          ok = true;
          break;
        }
      }
      if (ok) {
        res.emplace_back(x, y);
      }
    }
  }
  return res;
}

eq_ans solve_mod2() {
  std::array<int64_t, 4> rems = {7, 19, 31, 43};
  eq_ans res;
  for (int64_t x = 0; x < 60; ++x) {
    for (int64_t y = 0; y < 60; ++y) {
      int64_t k = 3*x*x + y*y;
      bool ok = false;
      for (int64_t r : rems) {
        if (k % 60 == r) {
          ok = true;
          break;
        }
      }
      if (ok) {
        res.emplace_back(x, y);
      }
    }
  }
  return res;
}

eq_ans solve_mod3() {
  std::array<int64_t, 4> rems = {11, 23, 47, 59};
  eq_ans res;
  for (int64_t x = 0; x < 60; ++x) {
    for (int64_t y = 0; y < 60; ++y) {
      int64_t k = 3*x*x - y*y + 3600;
      bool ok = false;
      for (int64_t r : rems) {
        if (k % 60 == r) {
          ok = true;
          break;
        }
      }
      if (ok) {
        res.emplace_back(x, y);
      }
    }
  }
  return res;
}

constexpr int64_t interval_size = 60;

std::array<std::function<eq_ans(void)>, 3> solve_mod_eq = {
  solve_mod1,
  solve_mod2,
  solve_mod3
};

std::vector<uint64_t> prime_list_under_interval(const uint64_t n) {
  std::vector<uint64_t> res;
  for (uint64_t i = 2; i <= n; ++i) {
    bool ok = true;
    for (uint64_t j = 2; j*j <= i; ++j)
      if ((i % j) == 0) ok = false;
    if (ok) res.push_back(i);
  }
  return res;
}

void sieve3_impl(std::vector<bool> &bit_ary,
    int64_t f, int64_t g,
    uint64_t L, uint64_t B) {
  int64_t x = f, y0 = g;
  int64_t k0 = 3*f*f - g*g;
  while (true) {
    bool brk = false;
    while (k0 >= (int64_t)(L+B)) {
      if (x <= y0) {
        brk = true;
        break;
      }
      k0 -= (2*y0 + 60)*60;
      y0 += 60;
    }
    if (brk) break;
    int64_t k = k0, y = y0;
    while (k >= (int64_t)L && y < x) {
      bit_ary[k-L] = !bit_ary[k-L];
      k -= (2*y + 60)*60;
      y += 60;
    }
    k0 += (6*x + 180)*60;
    x += 60;
  }
}

template <int a, int b>
void sieve_impl(std::vector<bool> &bit_ary,
    int64_t f, int64_t g,
    uint64_t L, uint64_t B) {
  int64_t x = f, y0 = g;
  int64_t k0 = a*f*f + b*g*g;
  while (k0 < (int64_t)(L+B)) {
    k0 += a*(2*x + 60)*60;
    x += 60;
  }
  while (true) {
    x -= 60;
    k0 -= a*(2*x + 60)*60;
    if (x <= 0) break;
    while (k0 < (int64_t)L) {
      k0 += b*(2*y0 + 60)*60;
      y0 += 60;
    }
    int64_t k = k0, y = y0;
    while (k < (int64_t)(L+B)) {
      bit_ary[k-L] = !bit_ary[k-L];
      k += b*(2*y + 60)*60;
      y += 60;
    }
  }
}

void sieve1(std::vector<bool> &bit_ary, const eq_ans &ans,
    uint64_t L, uint64_t B) {
  for (auto sp_ans : ans) {
    int64_t f, g;
    std::tie(f, g) = sp_ans;
    sieve_impl<4, 1>(bit_ary, f, g, L, B);
  }
}

void sieve2(std::vector<bool> &bit_ary, const eq_ans &ans,
    uint64_t L, uint64_t B) {
  for (auto sp_ans : ans) {
    int64_t f, g;
    std::tie(f, g) = sp_ans;
    sieve_impl<3, 1>(bit_ary, f, g, L, B);
  }
}

void sieve3(std::vector<bool> &bit_ary, const eq_ans &ans,
    uint64_t L, uint64_t B) {
  for (auto sp_ans : ans) {
    int64_t f, g;
    std::tie(f, g) = sp_ans;
    sieve3_impl(bit_ary, f, g, L, B);
  }
}

void sieve_non_squarefree(std::vector<bool> &bit_ary, uint64_t L, uint64_t B,
    const std::vector<uint64_t> &primes) {
  for (uint64_t p : primes) {
    uint64_t psq = p*p;
    if (psq > L+B) break;
    if (p >= 7) {
      uint64_t r = L % psq;
      uint64_t s = r ? (psq - r) : 0;
      for (; s < B; s += psq)
        bit_ary[s] = false;
    }
  }
}

std::vector<bool> sieve_interval(const uint64_t L, const uint64_t B,
    const std::vector<eq_ans> &eq_ans_list,
    const std::vector<uint64_t> &primes) {
  std::vector<bool> bit_ary(B, false);
  sieve1(bit_ary, eq_ans_list[0], L, B);
  sieve2(bit_ary, eq_ans_list[1], L, B);
  sieve3(bit_ary, eq_ans_list[2], L, B);
  sieve_non_squarefree(bit_ary, L, B, primes);
  return bit_ary;
}

std::vector<uint64_t> prime_list(const uint64_t n) {
  if (n <= interval_size) {
    return prime_list_under_interval(n);
  }
  uint64_t sqn = sqrt(n+0.5);
  uint64_t B = interval_size * sqn;
  auto primes = prime_list(sqn);
  std::vector<uint64_t> res = prime_list_under_interval(5);
  std::vector<eq_ans> eq_ans_list;
  for (auto func : solve_mod_eq)
    eq_ans_list.emplace_back(func());
  for (uint64_t L = 1; L <= n; L += B) {
    auto bit_ary = sieve_interval(L, B, eq_ans_list, primes);
    for (uint64_t i = 0; i < B; ++i) {
      if (L + i > n) break;
      if (bit_ary[i]) {
        int r = (L + i) % 12;
        int rs[] = {1, 5, 7, 11};
        for (int j = 0; j < 4; ++j) {
          if (r == rs[j]) res.push_back(L+i);
        }
      }
    }
  }
  return res;
}

void count_interval(const uint64_t L, const uint64_t B, const uint64_t n,
    std::vector<eq_ans> &eq_ans_list, std::vector<uint64_t> &primes,
    std::vector<uint64_t> &count) {
  auto bit_ary = sieve_interval(L, B, eq_ans_list, primes);
  uint64_t sum = (L < B) ? 3 : 0;
  for (uint64_t i = 0; i < B; ++i) {
    if (L + i > n) break;
    if (bit_ary[i]) {
      int r = (L + i) % 12;
      int rs[] = {1, 5, 7, 11};
      for (int j = 0; j < 4; ++j) {
        if (r == rs[j]) ++sum;
      }
    }
  }
  count[L/B] = sum;
}

result::result sieve_of_atkin_interval(const uint64_t n) {
  const uint64_t sqn = sqrt(n+0.5);
  const uint64_t B = interval_size * sqn;
  auto primes = prime_list(sqn);
  std::vector<eq_ans> eq_ans_list;
  for (auto func : solve_mod_eq)
    eq_ans_list.emplace_back(func());
  result::result res(n, B);
  for (uint64_t L = 1; L <= n; L += B) {
    count_interval(L, B, n, eq_ans_list, primes, res.count);
  }
  return res;
}

} // namespace prime_counter
