cmake_minimum_required(VERSION 3.23)
project(random_mage_generator_disjoint_set)

set(CMAKE_CXX_STANDARD 23)

add_executable(random_mage_generator_disjoint_set main.cpp maze.hpp disjoint-set.hpp maze-generator.hpp)

add_executable(random_mage_generator_benchmark maze.hpp disjoint-set.hpp maze-generator.hpp maze-benchmark.cpp)
find_package(benchmark REQUIRED)
target_link_libraries(random_mage_generator_benchmark benchmark::benchmark)