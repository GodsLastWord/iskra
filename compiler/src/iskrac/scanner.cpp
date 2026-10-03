#include "iskrac/scanner.hpp"

#include "iskrac/is_x.hpp"
#include "iskrac/lexemes_to_kinds.hpp"
#include "iskrac/tokens.hpp"
#include <print>

namespace iskrac {

Scanner::Scanner(
    SourceText& source,
    StringSpace& strings,
    ErrorFormatter& errfmt)
    : source{ source }
    , strings{ strings }
    , errfmt{ errfmt } {
}

Token Scanner::next() {

    Token token;

    switch (getState(peek())) {
        case State::ERROR:
            token = scanError();
            break;

        case State::_EOF:
            token = scanEof();
            break;

        case State::NUMBER:
            token = scanNumber();
            break;

        case State::OPERATOR:
            token = scanOperator();
            break;

        case State::BRACKET:
            token = scanBracket();
            break;

        case State::SPACE:
            skipWhitespace();
            return next();

        default:
            token = {
                Token::Kind::ERROR,
                strings.add({ char(source.peek()) }),
                currentPosition(),
            };
    }

    if (isErrorTokenKind(token.kind)) {
        handleError(token);
        return next();
    }

    return token;
}

auto Scanner::getState(int c) -> State {

    if (source.eof()) {
        return State::_EOF;
    }

    if (isDigit(c)) {
        return State::NUMBER;
    }

    if (isOperator(c)) {
        return State::OPERATOR;
    }

    if (isBracket(c)) {
        return State::BRACKET;
    }

    if (isSpace(c)) {
        return State::SPACE;
    }

    return State::ERROR;
}

Token Scanner::scanError() {
    Position position = currentPosition();
    std::string buf;

    for (int c = peek(); getState(c) == State::ERROR; c = advance()) {
        buf += char(c);
    }

    return { Token::Kind::UNRECOGNIZED, strings.add(buf), position };
}

Token Scanner::scanEof() {
    return { Token::Kind::_EOF, strings.add(""), currentPosition() };
}

Token Scanner::scanNumber() {
    Token::Kind kind = Token::Kind::INT32_LITERAL;
    Position position = currentPosition();
    std::string buf;

    for (int c = peek(); isDigit(c); c = advance()) {
        buf += char(c);
    }

    if (!isValidInt32Literal(buf)) {
        kind = Token::Kind::INVALID_INT32_LITERAL;
    }

    return { kind, strings.add(buf), position };
}

Token Scanner::scanOperator() {
    Position position = currentPosition();
    std::string buf{ char(peek()) };

    while (isOperator(buf)) {
        buf += advance();
    }
    buf.pop_back();

    return { OPERATORS.at(buf), strings.add(buf), position };
}

Token Scanner::scanBracket() {
    Position position = currentPosition();
    std::string buf{ char(peek()) };

    while (isBracket(buf)) {
        buf += advance();
    }
    buf.pop_back();

    return { BRACKETS.at(buf), strings.add(buf), position };
}

void Scanner::skipWhitespace() {
    while (isSpace(peek())) {
        advance();
    }
}

Position Scanner::currentPosition() {
    return { lineCounter, columnCounter, lastLineStart };
}

bool Scanner::isErrorTokenKind(Token::Kind kind) {
    using TK = Token::Kind;

    switch (kind) {
        case TK::PLACEHOLDER:
        case TK::ERROR:
        case TK::UNRECOGNIZED:
        case TK::INVALID_INT32_LITERAL:
            return true;
        default:
            return false;
    }
}

int Scanner::peek() {
    return source.peek();
}

int Scanner::advance() {

    if (peek() == '\n') {
        lineCounter++;
        columnCounter = 0;
    }
    columnCounter++;

    source.advance();
    lastLineStart = source.absoluteCurrentPosition();

    return peek();
}

void Scanner::handleError(const Token& error) {
    using TK = Token::Kind;
    
    switch (error.kind) {
        case TK::PLACEHOLDER:
            errfmt.error(error, "placeholder token has been produced");
            break;
        case TK::ERROR:
            errfmt.error(error, "internal error occurred while scanning");
            break;
        case TK::UNRECOGNIZED:
            errfmt.error(error, "unrecognized lexeme was found");
            break;
        case TK::INVALID_INT32_LITERAL:
            errfmt.error(error, "invalid `int32` literal format");
            break;
        default:
            errfmt.error(error, "unknown occurred");
    }
}

} // namespace iskrac
