#pragma once

#include <cstddef>

#include "interfaces.hpp"
#include "iskrac/string_space.hpp"

namespace iskrac::visitor {

class ASTPrinter : public ExpressionVisitor {
    const std::size_t TAB_LENGTH{ 4 };
    std::size_t tabDepth{ 0 };

    const StringSpace& strings;

public:
    explicit ASTPrinter(const StringSpace&);

    void visit(const ast::Expression&);
    void visit(const ast::InvalidExpression&);
    void visit(const ast::LiteralExpression&);
    void visit(const ast::BinaryExpression&);
    void visit(const ast::UnaryExpression&);

private:
    void tab();
    void inner();
    void outer();
};

} // namespace iskrac::visitor
