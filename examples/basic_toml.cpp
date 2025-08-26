#include <iostream>
#include <serde/toml.hpp>

struct Config {
    std::string name;
    int port;
};

// Manual specialization
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

int main() {
    auto cfg_result = serde::from_toml<Config>("config.toml");

    if (cfg_result) {
        auto cfg = cfg_result.value();
        std::cout << "Server: " << cfg.name 
                  << " Port: " << cfg.port << "\n";
    } else {
        std::cerr << "Error: " << cfg_result.error() << "\n";
    }
}
