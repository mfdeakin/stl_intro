
#include <benchmark/benchmark.h>

#include <execution>
#include <functional>
#include <numeric>
#include <random>

constexpr size_t num_elems = 1 << 28;

static void transform_bench(benchmark::State &state) {
  std::vector<double> v;
  for (size_t i = 0; i < num_elems; ++i) {
    v.push_back(1.0 / i);
  }
  std::mt19937_64 rng((std::random_device())());
  std::shuffle(v.begin(), v.end(), rng);

  std::vector<double> result(v.size());
  for (auto _ : state) {
    std::transform(v.begin(), v.end(), result.begin(), [](const double &inp) {
      return std::sqrt(inp * 3.14159265 + 2.718281828);
    });
  }
}
BENCHMARK(transform_bench);

static void transform_par_bench(benchmark::State &state) {
  std::vector<double> v;
  for (size_t i = 0; i < num_elems; ++i) {
    v.push_back(1.0 / i);
  }
  std::mt19937_64 rng((std::random_device())());
  std::shuffle(v.begin(), v.end(), rng);

  std::vector<double> result(v.size());
  for (auto _ : state) {
    std::transform(std::execution::par, v.begin(), v.end(), result.begin(),
                   [](const double &inp) {
                     return std::sqrt(inp * 3.14159265 + 2.718281828);
                   });
  }
}
BENCHMARK(transform_par_bench);

static void reduce_bench(benchmark::State &state) {
  std::vector<double> v;
  for (size_t i = 0; i < num_elems; ++i) {
    v.push_back(1.0 / i);
  }
  std::mt19937_64 rng((std::random_device())());
  std::shuffle(v.begin(), v.end(), rng);

  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    benchmark::DoNotOptimize(std::reduce(v.begin(), v.end()));
  }
}
BENCHMARK(reduce_bench);

static void reduce_par_bench(benchmark::State &state) {
  std::vector<double> v;
  for (size_t i = 0; i < num_elems; ++i) {
    v.push_back(1.0 / i);
  }
  std::mt19937_64 rng((std::random_device())());
  std::shuffle(v.begin(), v.end(), rng);

  for (auto _ : state) {
    benchmark::DoNotOptimize(
        std::reduce(std::execution::par, v.begin(), v.end()));
  }
}
// Register the function as a benchmark
BENCHMARK(reduce_par_bench);

static void scan_bench(benchmark::State &state) {
  std::vector<double> v;
  for (size_t i = 0; i < num_elems; ++i) {
    v.push_back(1.0 / i);
  }
  std::mt19937_64 rng((std::random_device())());
  std::shuffle(v.begin(), v.end(), rng);

  std::vector<double> result(v.size());
  for (auto _ : state) {
    std::inclusive_scan(v.begin(), v.end(), result.begin());
  }
}
BENCHMARK(scan_bench);

static void scan_par_bench(benchmark::State &state) {
  std::vector<double> v;
  for (size_t i = 0; i < num_elems; ++i) {
    v.push_back(1.0 / i);
  }
  std::mt19937_64 rng((std::random_device())());
  std::shuffle(v.begin(), v.end(), rng);

  std::vector<double> result(v.size());
  for (auto _ : state) {
    std::inclusive_scan(std::execution::par, v.begin(), v.end(),
                        result.begin());
  }
}
// Register the function as a benchmark
BENCHMARK(scan_par_bench);

static void shuffle_bench(benchmark::State &state) {
  std::vector<double> v;
  for (size_t i = 0; i < num_elems; ++i) {
    v.push_back(1.0 / i);
  }
  std::mt19937_64 rng((std::random_device())());

  for (auto _ : state) {
    std::shuffle(v.begin(), v.end(), rng);
  }
}
BENCHMARK(shuffle_bench);

static void sort_bench(benchmark::State &state) {
  std::vector<double> v;
  for (size_t i = 0; i < num_elems; ++i) {
    v.push_back(1.0 / i);
  }
  std::mt19937_64 rng((std::random_device())());

  std::vector<double> result(v.size());
  for (auto _ : state) {
    std::shuffle(v.begin(), v.end(), rng);
    std::sort(v.begin(), v.end());
  }
}
BENCHMARK(sort_bench);

static void sort_par_bench(benchmark::State &state) {
  std::vector<double> v;
  for (size_t i = 0; i < num_elems; ++i) {
    v.push_back(1.0 / i);
  }
  std::mt19937_64 rng((std::random_device())());
  std::shuffle(v.begin(), v.end(), rng);

  for (auto _ : state) {
    std::shuffle(v.begin(), v.end(), rng);
    std::sort(std::execution::par, v.begin(), v.end());
  }
}
BENCHMARK(sort_par_bench);

BENCHMARK_MAIN();
