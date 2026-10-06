#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace iskra {

namespace {

template<typename T>
using Bytes = std::array<std::uint8_t, sizeof(T)>;

template<typename T, std::size_t... indecies>
auto bytesTo_implementation(const Bytes<T>& bytes) -> T {
    T value;
    std::uint8_t* ptr = &value;

    ((ptr[indecies] = bytes[sizeof(T) - indecies - 1]), ...);

    return value;
}

} // namespace

template<typename T>
    requires std::is_arithmetic_v<T>
auto bytesTo(const Bytes<T>& bytes) -> T {
    return bytesTo_implementation(bytes, std::make_index_sequence<sizeof(T)>{});
}

} // namespace iskra
