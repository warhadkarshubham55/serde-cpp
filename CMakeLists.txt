cmake_minimum_required(VERSION 3.14)

project(serde-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

enable_testing()
add_subdirectory(tests)


# Fetch toml11 (header-only, skip its CMakeLists.txt)
FetchContent_Declare(
    toml11
    GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
    GIT_TAG master   # or v3.9.0 if available
)

FetchContent_GetProperties(toml11)
if(NOT toml11_POPULATED)
    FetchContent_Populate(toml11)
endif()

set(TOML11_INCLUDE_DIR ${toml11_SOURCE_DIR})

# Main library (header-only, just an interface target)
add_library(serde-cpp INTERFACE)
target_include_directories(serde-cpp INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include   # your serde headers
    ${TOML11_INCLUDE_DIR}                 # toml11 headers
)

# Example program
add_executable(basic_toml examples/basic_toml.cpp)
target_link_libraries(basic_toml PRIVATE serde-cpp)
