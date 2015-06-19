#include "utils.hpp"

#include <cstdio>
#include <cstdint>
#include <cinttypes>

namespace utils {

void output_result(const result::result &res) {
  printf("%" PRIu64 " %" PRIu64 "\n", res.n, res.interval_size);
  for (uint64_t cnt : res.count) {
    printf("%" PRIu64 "\n", cnt);
  }
}

} // namespace utils
