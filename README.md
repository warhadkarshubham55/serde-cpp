serde-cpp is a modern, header-only C++17+ library inspired by Rust’s Serde
.
It provides generic serialization and deserialization support for C++ structs across multiple data formats.

✅ Zero boilerplate: Structs automatically map to TOML/JSON/YAML via reflection.

✅ Multi-format: TOML (via toml11/toml++), JSON (via nlohmann/json), and more in future.

✅ Safe & expressive: Errors are handled via std::expected<T, Error> (C++23) or exceptions.

✅ Extensible: Add new backends with minimal effort.

✅ Header-only: Easy integration with modern C++ projects.
