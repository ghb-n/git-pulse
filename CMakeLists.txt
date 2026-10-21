cmake_minimum_required(VERSION 3.15)
project(git_pulse VERSION 1.0.0 LANGUAGES CXX)

# Require C++17 or C++20 for std::filesystem
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/include)

# Add source files
add_executable(git_pulse
    src/main.cpp
    src/scanner.cpp
)
