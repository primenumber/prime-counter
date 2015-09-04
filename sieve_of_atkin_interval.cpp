#include "prime_counter.hpp"
#include <cmath>
#include <algorithm>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <tuple>
#include <vector>

#include <boost/dynamic_bitset.hpp>

#include "sieve_impl.hpp"

namespace prime_counter {

constexpr int64_t interval_size = 60;

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

void sieve_non_squarefree(boost::dynamic_bitset<> &bit_ary, uint64_t L, uint64_t B,
    const std::vector<uint64_t> &primes) {
  for (uint64_t p : primes) {
    uint64_t psq = p*p;
    if (psq > L+B) break;
    if (p >= 7) {
      uint64_t r = L % psq;
      uint64_t s = r ? (psq - r) : 0;
      for (; s < B; s += psq)
        bit_ary.set(s, false);
    }
  }
}

boost::dynamic_bitset<> sieve_interval(const uint64_t L, const uint64_t B,
    const std::vector<uint64_t> &primes) {
  boost::dynamic_bitset<> bit_ary(B);
  sieve1(bit_ary, L, B);
  sieve2(bit_ary, L, B);
  sieve3(bit_ary, L, B);
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
  init_sieve();
  for (uint64_t L = 1; L <= n; L += B) {
    auto bit_ary = sieve_interval(L, B, primes);
    for (uint64_t i = 0; i < B; ++i) {
      if (L + i > n) break;
      if (bit_ary.test(i)) {
        int r = (L + i) % 12;
        int rs[] = {1, 5, 7, 11};
        for (int j = 0; j < 4; ++j) {
          if (r == rs[j] && L+i > 5) res.push_back(L+i);
        }
      }
    }
  }
  return res;
}

std::mutex mtx;

void count_interval(const uint64_t L, const uint64_t B, const uint64_t n,
    const std::vector<uint64_t> &primes, std::vector<uint64_t> &count,
    const boost::dynamic_bitset<> &mask, const uint64_t sqn) {
  auto bit_ary = sieve_interval(L, B, primes) & mask;
  std::vector<int64_t> count_sub(interval_size, 0);
  if (L <= 2 && L+B >= 2) bit_ary.set(2-L);
  if (L <= 3 && L+B >= 3) bit_ary.set(3-L);
  if (L <= 5 && L+B >= 5) bit_ary.set(5-L);
  for (int64_t i = 0; i < B && L+i <= n; ++i) {
    if (bit_ary.test(i)) count_sub[i/sqn]++;
  }
  mtx.lock();
  for (int64_t i = 0; i < interval_size && L+i*sqn <= n; ++i)
    count[L/sqn + i] = count_sub[i];
  mtx.unlock();
}

result::result sieve_of_atkin_interval(const uint64_t n) {
  const uint64_t sqn = sqrt(n+0.5);
  const uint64_t B = interval_size * sqn;
  auto primes = prime_list(sqn);
  std::vector<eq_ans> eq_ans_list;
  init_sieve();
  boost::dynamic_bitset<> mask(B);
  for (uint64_t i = 0; i < B; ++i) {
    switch((1+i) % 12) {
      case 1:
      case 5:
      case 7:
      case 11:
        mask.set(i);
    }
  }
  result::result res(n, sqn);
  std::vector<std::thread> th;
  const int thread_num = std::thread::hardware_concurrency();
  std::cerr << thread_num << " threads" << std::endl;
  for (uint64_t i = 0; i < thread_num; ++i) {
    th.emplace_back(std::thread([&,i=i]{
      for (uint64_t L = 1 + B*i; L <= n; L += B*thread_num) {
        std::cerr << L << std::endl;
        count_interval(L, B, n, primes, res.count, mask, sqn);
      }
    }));
  }
  for (auto &t : th) t.join();
  return res;
}

} // namespace prime_counter
