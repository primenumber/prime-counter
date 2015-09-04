cmake_minimum_required(VERSION 2.8)
project(PRIME_COUNTER)
add_definitions("-std=c++14 -g -O3 -flto -march=native -mtune=native -Wall -Wextra -Weffc++")
add_executable(prc
  main.cpp
  utils.cpp
  sieve_of_atkin_interval.cpp
  sieve_4k_1.cpp
  sieve_12k_7.cpp
  sieve_12k_11.cpp
)
target_link_libraries(prc pthread)
