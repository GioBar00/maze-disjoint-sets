#include <benchmark/benchmark.h>
#include "maze-generator.hpp"

static void BM_ForestDisjointSet(benchmark::State &state)
{
    int rows = state.range(0);
    int columns = state.range(1);
    int n = rows * columns;

    for (auto _ : state)
        benchmark::DoNotOptimize(randomMazeForest<int>(rows, columns));

    state.SetComplexityN(n);
}

BENCHMARK(BM_ForestDisjointSet)
    ->RangeMultiplier(2)
    ->Ranges({{2, 1 << 8}, {2, 1 << 15}})
    ->Complexity();

BENCHMARK_MAIN();
