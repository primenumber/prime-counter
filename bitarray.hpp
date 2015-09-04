#pragma once
#include <cassert>
#include <cstddef>
#include <vector>
#include <utility>

namespace prime_counter {

class bitarray {
 public:
  bitarray(std::size_t sz)
    : data((sz+63)/64, 0), sz(sz) {}
  bool test(std::size_t index) const {
    assert(index < sz);
    return (data[lower_index(index)] >> (index & 0x3F)) & 1;
  }
  void set(std::size_t index) {
    assert(index < sz);
    data[lower_index(index)] |= UINT64_C(1) << (index & 0x3F);
  }
  void set(std::size_t index, bool b) {
    if (b) set(index);
    else reset(index);
  }
  void reset(std::size_t index) {
    assert(index < sz);
    data[lower_index(index)] &= ~(UINT64_C(1) << (index & 0x3F));
  }
  void flip(std::size_t index) {
    assert(index < sz);
    data[lower_index(index)] ^= UINT64_C(1) << (index & 0x3F);
  }
  std::size_t size() const { return sz; }
  std::size_t count() const {
    std::size_t sum = 0;
    for (uint64_t v : data) sum += popcount(v);
    return sum;
  }
  std::size_t count(std::size_t first, std::size_t last) const {
    std::size_t sum = 0;
    sum += popcount(data[lower_index(first)] & (~0 << first & 0x3F));
    sum += popcount(data[lower_index(last)] & (~0 >> (63-(first & 0x3F))));
    for (std::size_t i = upper_index(first); i < lower_index(last); ++i) {
      sum += popcount(data[i]);
    }
    return sum;
  }
  bitarray &operator&=(const bitarray &rhs) {
    std::size_t size_min = std::min(data.size(), rhs.data.size());
    for (std::size_t i = 0; i < size_min; ++i)
      data[i] &= rhs.data[i];
    for (std::size_t i = size_min; i < data.size(); ++i)
      data[i] = 0;
    return *this;
  }
  bitarray &operator|=(const bitarray &rhs) {
    for (std::size_t i = 0; i < std::min(sz, rhs.sz); ++i)
      data[i] |= rhs.data[i];
    return *this;
  }
 private:
  static std::size_t upper_index(std::size_t n) { return (n+63) >> 6; }
  static std::size_t lower_index(std::size_t n) { return n >> 6; }
  static std::size_t ceil_64(std::size_t n) {
    return (n & 0x3F) ? ((n | 0x3F) + 1) : n;
  }
  static std::size_t floor_64(std::size_t n) { return n & ~0x3F; }
  static std::size_t popcount(uint64_t bits) {
    return __builtin_popcount(bits);
  }
  std::vector<uint64_t> data;
  std::size_t sz;
};

inline bitarray operator&(const bitarray &lhs, const bitarray &rhs) {
  auto res = lhs;
  return res &= rhs;
}

inline bitarray operator|(const bitarray &lhs, const bitarray &rhs) {
  auto res = lhs;
  return res |= rhs;
}

} // namespace prime_counter
