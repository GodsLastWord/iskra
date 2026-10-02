#include "iskrac/lexemes_to_kinds.hpp"

namespace iskrac {

using enum Token::Kind;

const std::map<std::string, Token::Kind> OPERATORS{
    { "+", PLUS    },
    { "-", MINUS   },
    { "*", STAR    },
    { "/", SLASH   },
    { "%", PERCENT },
};

const std::map<std::string, Token::Kind> BRACKETS{
    { "(", L_ROUND },
    { ")", R_ROUND },
};

} // namespace iskrac
