#pragma once

#include "../tokens.hpp"
#include "../visitors/interfaces.hpp"
#include "forwards.hpp"

namespace iskrac::ast {

struct Expression {
    virtual ~Expression() = default;
    explicit Expression() = default;

    explicit Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;

    explicit Expression(Expression&&) = delete;
    Expression& operator=(Expression&&) = delete;

    virtual void accept(visitor::ExpressionVisitor&) const = 0;
};

struct InvalidExpression : public Expression {
    const Token error;

    explicit InvalidExpression(Token error)
        : error{ error } {
    }

    void accept(visitor::ExpressionVisitor& v) const override {
        v.visit(*this);
    }
};

struct LiteralExpression : public Expression {
    const Token literal;

    explicit LiteralExpression(Token literal)
        : literal{ literal } {
    }

    void accept(visitor::ExpressionVisitor& v) const override {
        v.visit(*this);
    }
};

struct BinaryExpression : public Expression {
    const Token operation;
    const Expression* left;
    const Expression* right;

    explicit BinaryExpression(Token operation, const Expression* left, const Expression* right)
        : operation{ operation }
        , left{ left }
        , right{ right } {
    }

    ~BinaryExpression() override {
        delete left;
        delete right;
    }

    void accept(visitor::ExpressionVisitor& v) const override {
        v.visit(*this);
    }
};

struct UnaryExpression : public Expression {
    const Token operation;
    const Expression* right;

    explicit UnaryExpression(Token operation, const Expression* right)
        : operation{ operation }
        , right{ right } {
    }

    ~UnaryExpression() override {
        delete right;
    }

    void accept(visitor::ExpressionVisitor& v) const override {
        v.visit(*this);
    }
};

} // namespace iskrac::ast
