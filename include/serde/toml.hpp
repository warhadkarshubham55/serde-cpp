#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <toml.hpp>
#include "result.hpp"

namespace serde {

template<typename T>
struct TomlConvert; // User must specialize this for their type

template<typename T>
Result<T> from_toml(const std::string& path) {
    try {
        auto data = toml::parse(path);
        return TomlConvert<T>::from_toml(data);
    } catch (const std::exception& e) {
        return Result<T>(std::string("TOML parse error: ") + e.what());
    }
}

template<typename T>
Result<void> to_toml(const T& value, const std::string& path) {
    try {
        auto toml_value = TomlConvert<T>::to_toml(value);
        std::ofstream ofs(path);
        ofs << toml_value;
        return Result<void>({});
    } catch (const std::exception& e) {
        return Result<void>(std::string("TOML write error: ") + e.what());
    }
}

} // namespace serde
