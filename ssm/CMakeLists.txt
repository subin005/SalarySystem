cmake_minimum_required(VERSION 3.20)

project(slary_system)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include_directories(scr/function)
# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/assent)

# configure_file(
#     ${CMAKE_SOURCE_DIR}/assent/member_data.txt
#     ${CMAKE_BINARY_DIR}/assent/member_data.txt
#     COPYONLY
# )

add_executable(ssm src/main.cpp src/function/funclib.hpp src/memory/contain.hpp src/function/funclib.cpp)

