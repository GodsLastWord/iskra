#include "iskrac/visitors/ast_printer.hpp"

#include <print>

#include "iskrac/ast/expressions.hpp"

namespace iskrac::visitor {

ASTPrinter::ASTPrinter(const StringSpace& strings)
    : strings{ strings } {
}

void ASTPrinter::visit(const ast::Expression& expr) {
    expr.accept(*this);
}

void ASTPrinter::visit(const ast::InvalidExpression& expr) {
    tab();
    std::println("(invalid `{}`)", strings.get(expr.error.lexeme));
}

void ASTPrinter::visit(const ast::LiteralExpression& expr) {
    tab();
    std::println("(literal `{}`)", strings.get(expr.literal.lexeme));
}

void ASTPrinter::visit(const ast::BinaryExpression& expr) {
    tab();
    std::println("(binary `{}`", strings.get(expr.operation.lexeme));

    inner();
    expr.left->accept(*this);
    expr.right->accept(*this);
    outer();

    tab();
    std::println(")");
}

void ASTPrinter::visit(const ast::UnaryExpression& expr) {
    tab();
    std::println("(unary `{}`", strings.get(expr.operation.lexeme));

    inner();
    expr.right->accept(*this);
    outer();

    tab();
    std::println(")");
}

void ASTPrinter::tab() {
    std::print("{:>{}}", "", tabDepth * TAB_LENGTH);
}

void ASTPrinter::inner() {
    tabDepth++;
}

void ASTPrinter::outer() {
    tabDepth--;
}

} // namespace iskrac::visitor
