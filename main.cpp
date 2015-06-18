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
  uint64_t n = atoi(argv[1]);
  auto result = prime_counter::sieve_of_atkin(n);
  utils::output_result(result);
  return 0;
}
