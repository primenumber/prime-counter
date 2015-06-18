cmake_minimum_required(VERSION 2.8)
project(PRIME_COUNTER)
add_definitions("-std=c++14 -O3 -flto -march=native -mtune=native -Wall -Wextra -Weffc++")
add_executable(prc
  main.cpp
  utils.cpp
  naive.cpp
  opti_for_2.cpp
  sieve_of_atkin.cpp
)
