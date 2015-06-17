#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage prc [number]\n");
    exit(1);
  }
  uint64_t n = atoi(argv[1]);
  auto result = naive::prime_count(n);
  utils::output_result(result);
  return 0;
}
