#include <iostream>
#include <cassert>
#include <serde/toml.hpp>

// Same Config struct as in your main program
struct Config {
    std::string name;
    int port;
};

// Manual specialization for serde::TomlConvert
namespace serde {
    template<>
    struct TomlConvert<Config> {
        static Config from_toml(const toml::value& v) {
            return {
                toml::find<std::string>(v, "name"),
                toml::find<int>(v, "port")
            };
        }
        static toml::value to_toml(const Config& c) {
            return toml::value{
                {"name", c.name},
                {"port", c.port}
            };
        }
    };
}

// ✅ Test: valid config file
void test_valid_config() {
    auto cfg_result = serde::from_toml<Config>("examples/config.toml");

    assert(cfg_result.has_value());
    auto cfg = cfg_result.value();

    assert(cfg.name == "MyServer");   // adjust according to config.toml
    assert(cfg.port == 8080);         // adjust according to config.toml

    std::cout << "[PASS] test_valid_config\n";
}

// ✅ Test: invalid file path
void test_invalid_path() {
    auto cfg_result = serde::from_toml<Config>("config.toml");

    assert(!cfg_result.has_value());
    std::cout << "[PASS] test_invalid_path\n";
}

// ✅ Test: invalid schema (missing fields)
void test_invalid_schema() {
    auto cfg_result = serde::from_toml<Config>("bad_config.toml");

    assert(!cfg_result.has_value());  // should fail due to missing keys
    std::cout << "[PASS] test_invalid_schema\n";
}

int main() {
    test_valid_config();
    test_invalid_path();
    test_invalid_schema();
    return 0;
}
