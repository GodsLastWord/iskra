#include "iskrac/is_x.hpp"

#include "iskrac/lexemes_to_kinds.hpp"

namespace iskrac {

bool isDigit(int c) {
    return '0' <= c && c <= '9';
}

bool isOperator(int c) {
    return std::find_if(OPERATORS.begin(), OPERATORS.end(), [c](auto& pair) -> bool {
        return pair.first.starts_with(static_cast<char>(c));
    }) != OPERATORS.end();
}

bool isBracket(int c) {
    return std::find_if(BRACKETS.begin(), BRACKETS.end(), [c](auto& pair) -> bool {
        return pair.first.starts_with(static_cast<char>(c));
    }) != BRACKETS.end();
}

bool isSpace(int c) {
    return std::isspace(c);
}

} // namespace iskrac
