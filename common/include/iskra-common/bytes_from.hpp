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

template<typename T, std::size_t... I>
auto bytesFrom_implementation(T value,  std::index_sequence<I...> indecies) -> Bytes<T> {
    Bytes<T> bytes;
    std::uint8_t* ptr = reinterpret_cast<std::uint8_t*>(&value);

    ((bytes[I] = ptr[sizeof(T) - I - 1]), ...);

    return bytes;
}

} // namespace

template<typename T>
    requires std::is_arithmetic_v<T>
inline auto bytesFrom(T value) -> Bytes<T> {
    return bytesFrom_implementation(value, std::make_index_sequence<sizeof(T)>{});
}

} // namespace iskra
