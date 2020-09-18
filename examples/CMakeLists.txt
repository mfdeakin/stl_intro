
cmake_minimum_required(VERSION 3.13.0)

project(stl_ex CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g ${OpenMP_CXX_FLAGS}")

add_executable(array_usage array_usage.cpp)
target_link_libraries(array_usage gtest gtest_main pthread)
add_executable(vector_usage vector_usage.cpp)
target_link_libraries(vector_usage gtest gtest_main pthread)
add_executable(map_usage map_usage.cpp)
target_link_libraries(map_usage gtest gtest_main pthread)
add_executable(set_usage set_usage.cpp)
target_link_libraries(set_usage gtest gtest_main pthread)

add_executable(algorithm_usage algorithm_usage.cpp)
target_link_libraries(algorithm_usage gtest pthread)

set(google_benchmark_path /usr/local CACHE PATH "Path to where Google Benchmark is installed")
link_directories("${google_benchmark_path}/lib")

add_executable(algorithm_benchmark algorithm_benchmark.cpp)
target_include_directories(algorithm_benchmark PUBLIC "${google_benchmark_path}/include")
target_link_libraries(algorithm_benchmark benchmark pthread tbb)
