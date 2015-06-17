#pragma once
#include <cstdint>
#include <vector>

namespace result {

struct result {
  uint64_t n;
  uint64_t interval_size;
  std::vector<uint64_t> count;
  result(uint64_t n, uint64_t interval_size)
    : n(n), interval_size(interval_size),
      count((n + interval_size - 1) / interval_size) {}
};

} // namespace result
