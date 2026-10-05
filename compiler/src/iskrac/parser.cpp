#include "iskrac/parser.hpp"

namespace iskrac {

using TK = Token::Kind;

const std::map<Token::Kind, ParseRule> Parser::parseRules{
    { TK::INT32_LITERAL, { Precedence::NONE, nullptr, &Parser::literal }           },
    { TK::PLUS,          { Precedence::ADDITION, &Parser::binary, &Parser::unary } },
    { TK::MINUS,         { Precedence::ADDITION, &Parser::binary, &Parser::unary } },
    { TK::STAR,          { Precedence::MULTIPLICATION, &Parser::binary, nullptr }  },
    { TK::SLASH,         { Precedence::MULTIPLICATION, &Parser::binary, nullptr }  },
    { TK::PERCENT,       { Precedence::MULTIPLICATION, &Parser::binary, nullptr }  },
    { TK::L_ROUND,       { Precedence::NONE, nullptr, &Parser::brackets }      },
};

Parser::Parser(SourceText& source, StringSpace& strings, ErrorFormatter& errfmt)
    : errfmt{ errfmt }
    , scan{ source, strings, errfmt } {

    advance();
    advance();
}

auto Parser::parse(SourceText& source, StringSpace& strings, ErrorFormatter& errfmt) -> std::unique_ptr<ast::Expression> {
    return Parser{ source, strings, errfmt }.parse();
}

auto Parser::parse() -> std::unique_ptr<ast::Expression> {
    return std::unique_ptr<ast::Expression>{ parseExpression() };
}

auto Parser::parseExpression(std::size_t currentPrecedence) -> ast::Expression* {
    auto rule = parseRules.find(currentToken.kind);

    if (rule == parseRules.end()) {
        errfmt.expected(currentToken, "a primary expression");
        return new ast::InvalidExpression{ currentToken };
    }

    ast::Expression* expr = (this->*rule->second.prefix)();

    while (true) {
        auto rule = parseRules.find(currentToken.kind);

        if (rule == parseRules.end()) {
            break;
        }

        if (rule->second.precedence <= currentPrecedence) {
            break;
        }

        if (!rule->second.infix) {
            break;
        }

        expr = (this->*rule->second.infix)(expr);
    }

    return expr;
}

auto Parser::literal() -> ast::Expression* {
    advance();
    return new ast::LiteralExpression{ previousToken };
}

auto Parser::unary() -> ast::Expression* {
    advance();
    Token operation = previousToken;
    return new ast::UnaryExpression{ operation, parseExpression(Precedence::UNARY) };
}

auto Parser::brackets() -> ast::Expression* {
    advance();

    ast::Expression* expr = parseExpression();

    consume({ Token::Kind::R_ROUND }, "`)`");

    return expr;
}

auto Parser::binary(ast::Expression* expr) -> ast::Expression* {
    advance();

    Token operation = previousToken;
    std::size_t precedence = parseRules.at(operation.kind).precedence;

    return new ast::BinaryExpression{
        operation,
        expr,
        parseExpression(precedence)
    };
}

void Parser::advance() {
    previousToken = currentToken;
    currentToken = nextToken;
    nextToken = scan.next();
}

void Parser::consume(std::initializer_list<Token::Kind> kinds, const std::string& message) {
    for (Token::Kind k : kinds) {
        if (currentToken.kind == k) {
            advance();
            return;
        }
    }

    advance();
    errfmt.expected(previousToken, "{}", message);
}

} // namespace iskrac
