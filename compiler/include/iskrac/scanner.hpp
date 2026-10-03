#pragma once

#include "error_formatter.hpp"
#include "source_text.hpp"
#include "string_space.hpp"
#include "tokens.hpp"

namespace iskrac {

class Scanner {

    enum class State {
        ERROR,
        _EOF,
        NUMBER,
        OPERATOR,
        BRACKET,
        SPACE,
    };

    SourceText& source;
    StringSpace& strings;
    ErrorFormatter& errfmt;

    std::size_t lineCounter{ 1 };
    std::size_t columnCounter{ 1 };
    std::streampos lastLineStart{ 0 };

public:
    explicit Scanner(SourceText&, StringSpace&, ErrorFormatter&);

    Token next();

private:
    auto getState(int) -> State;

    Token scanError();
    Token scanEof();
    Token scanNumber();
    Token scanOperator();
    Token scanBracket();
    void skipWhitespace();

    Position currentPosition();

    bool isErrorTokenKind(Token::Kind);

    int peek();
    int advance();

    void handleError(const Token&);
};

} // namespace iskrac
