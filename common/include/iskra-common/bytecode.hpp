#pragma once

#include <cstddef>
#include <cstdint>

namespace iskra::bytecode {

namespace header {

constexpr std::uint32_t MAGIC = 0xDEADC0DE;
constexpr std::uint16_t MAJOR = 0;
constexpr std::uint16_t MINOR = 0;

constexpr std::size_t SIZE = sizeof(MAGIC) + sizeof(MAJOR) + sizeof(MINOR);

} // namespace header

namespace instruction {

enum : std::uint8_t {
    NO_INSTRUCTION = 0x00,
    LOAD_CONSTANT = 0x01,
    I32_ADD = 0x02,
    I32_SUB = 0x03,
    I32_MUL = 0x04,
    I32_DIV = 0x05,
    I32_MOD = 0x06,
    I32_RETURN = 0x07,
};

} // namespace instruction

} // namespace iskra::bytecode
