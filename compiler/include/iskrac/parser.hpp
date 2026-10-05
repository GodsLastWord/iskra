#pragma once

#include <initializer_list>
#include <map>
#include <memory>

#include "ast/expressions.hpp"
#include "scanner.hpp"

namespace iskrac {

class Parser;

using InfixFunction = auto (Parser::*)(ast::Expression*) -> ast::Expression*;
using PrefixFunction = auto (Parser::*)() -> ast::Expression*;

struct Precedence {
    enum : std::size_t {
        NONE,
        ADDITION,
        MULTIPLICATION,
        UNARY,
    };
};

struct ParseRule {
    const std::size_t precedence{ Precedence::NONE };
    const InfixFunction infix;
    const PrefixFunction prefix;
};

class Parser {
    static const std::map<Token::Kind, ParseRule> parseRules;

    ErrorFormatter& errfmt;

    Scanner scan;
    Token previousToken;
    Token currentToken;
    Token nextToken;

public:
    explicit Parser(SourceText&, StringSpace&, ErrorFormatter&);

    static auto parse(SourceText&, StringSpace&, ErrorFormatter&)
        -> std::unique_ptr<ast::Expression>;

    auto parse() -> std::unique_ptr<ast::Expression>;

private:
    auto parseExpression(std::size_t = Precedence::NONE) -> ast::Expression*;
    auto literal() -> ast::Expression*;
    auto unary() -> ast::Expression*;
    auto brackets() -> ast::Expression*;
    auto binary(ast::Expression*) -> ast::Expression*;

    void advance();
    void consume(std::initializer_list<Token::Kind>, const std::string&);
};

} // namespace iskrac
