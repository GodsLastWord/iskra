#pragma once

#include <cstddef>
#include <iosfwd>

namespace iskrac {

struct Position {
    std::size_t line{ 0 };
    std::size_t column{ 0 };
    std::streampos lastLineStart{ 0 };
};

struct Token {
    enum class Kind {
        PLACEHOLDER,

        _EOF,

        ERROR,
        UNRECOGNIZED,

        INT32_LITERAL,

        PLUS,
        MINUS,
        STAR,
        SLASH,
        PERCENT,

        L_ROUND,
        R_ROUND,
    };

    Kind kind{ Kind::PLACEHOLDER };
    std::size_t lexeme{};
    Position position{};
};

} // namespace iskrac
