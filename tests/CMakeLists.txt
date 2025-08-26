# Tests CMake
add_executable(basic_toml_test basic_toml_test.cpp)

target_include_directories(basic_toml_test PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/build/_deps/toml11-src
)

target_link_libraries(basic_toml_test PRIVATE serde-cpp)

add_test(NAME basic_toml_test COMMAND basic_toml_test)
