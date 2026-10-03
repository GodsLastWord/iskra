#include "iskrac/is_x.hpp"

#include "iskrac/lexemes_to_kinds.hpp"

namespace iskrac {

bool isDigit(int c) {
    return '0' <= c && c <= '9';
}

bool isOperator(int c) {
    // clang-format off
    return std::find_if(
        OPERATORS.begin(),
        OPERATORS.end(),
        [c](auto& pair) -> bool {
            return pair.first.starts_with(static_cast<char>(c));
        }
    ) != OPERATORS.end();
    // clang-format on
}

bool isOperator(const std::string& s) {
    return OPERATORS.contains(s);
}

bool isBracket(int c) {
    // clang-format off
    return std::find_if(
        BRACKETS.begin(),
        BRACKETS.end(),
        [c](auto& pair) -> bool {
            return pair.first.starts_with(static_cast<char>(c));
        }
    ) != BRACKETS.end();
    // clang-format on
}

bool isBracket(const std::string& s) {
    return BRACKETS.contains(s);
}

bool isSpace(int c) {
    return std::isspace(c);
}

bool isValidInt32Literal(const std::string& literal) {
    for (char c : literal) {
        if (!isDigit(c)) return false;
    }

    try {
        [[maybe_unused]]
        int x = std::stoi(literal);
        return true;
    }

    catch (...) {
        return false;
    }
}

} // namespace iskrac
