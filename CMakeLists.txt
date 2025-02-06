cmake_minimum_required(VERSION 3.10)

# Project Name
project(Async_Load_Balancer)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost Libraries
find_package(Boost 1.66 REQUIRED COMPONENTS system)

# Include Directories
include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

# Source Files
set(SOURCES
    src/load_balancer.cpp
    src/main.cpp
)

# Executable
add_executable(async_load_balancer ${SOURCES})

# Link Libraries
target_link_libraries(async_load_balancer ${Boost_LIBRARIES})
