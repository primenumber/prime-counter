#include <cstdio>
#include <cstdlib>
#include "utils.hpp"
#include "result.hpp"
#include "prime_counter.hpp"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage prc [number]\n");
    exit(1);
  }
  uint64_t n = atol(argv[1]);
  auto result = prime_counter::sieve_of_atkin_interval(n);
  utils::output_result(result);
  return 0;
}
