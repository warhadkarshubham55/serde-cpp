#pragma once
#include <variant>
#include <string>
#include <optional>

namespace serde {

template<typename T>
class Result {
    std::variant<T, std::string> data;
public:
    Result(T value) : data(std::move(value)) {}
    Result(std::string error) : data(std::move(error)) {}

    bool has_value() const { return std::holds_alternative<T>(data); }
    explicit operator bool() const { return has_value(); }

    T& value() { return std::get<T>(data); }
    const T& value() const { return std::get<T>(data); }

    std::string error() const { return std::get<std::string>(data); }
};

} // namespace serde