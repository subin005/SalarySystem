cmake_minimum_required(VERSION 3.20)

project(slary_system)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include_directories(scr/function)
add_executable(slary_system src/main.cpp src/function/funclib.hpp src/function/contain.hpp scr/function/funclib.cpp)

