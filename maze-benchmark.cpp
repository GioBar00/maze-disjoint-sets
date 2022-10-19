#include <benchmark/benchmark.h>
#include "maze-generator.hpp"

static void BM_ForestDisjointSet(benchmark::State &state) {
    int rows = state.range(0);
    int columns = state.range(1);
    int walls = 2 * rows * columns - rows - columns;

    for (auto _ : state)
        benchmark::DoNotOptimize(randomMazeForest<int>(rows, columns));

    state.SetComplexityN(walls);
}

static void BM_LinkedListDisjointSet(benchmark::State &state) {
    int rows = state.range(0);
    int columns = state.range(1);
    int walls = 2 * rows * columns - rows - columns;

    for (auto _ : state)
        benchmark::DoNotOptimize(randomMazeList<int>(rows, columns));

    state.SetComplexityN(walls);
}

BENCHMARK(BM_LinkedListDisjointSet)
    ->RangeMultiplier(2)
    ->Ranges({{2, 1 << 5}, {2, 1 << 14}})
    ->Complexity();

BENCHMARK(BM_ForestDisjointSet)
    ->RangeMultiplier(2)
    ->Ranges({{2, 1 << 7}, {2, 1 << 15}})
    ->Complexity();

BENCHMARK_MAIN();