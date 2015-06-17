#include "utils.hpp"

#include <cstdio>

namespace utils {

void output_result(const result::result &res) {
  printf("%d %d\n", res.n, res.interval_size);
  for (uint64_t cnt : res.count) {
    printf("%d\n", cnt);
  }
}
