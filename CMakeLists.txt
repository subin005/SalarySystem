cmake_minimum_required(VERSION 3.10)
project(COMPANY_MANAGEMENT_SYSTEM)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 源文件
set(SOURCES
    src/Person.cpp
    src/Manager.cpp
    src/Saleman.cpp
    src/Salemanager.cpp
    src/Technican.cpp
    src/main.cpp
)

# 生成可执行文件
add_executable(COMPANY_MANAGEMENT_SYSTEM ${SOURCES})

# 设置输出目录
set_target_properties(COMPANY_MANAGEMENT_SYSTEM PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)