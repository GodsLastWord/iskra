#include <filesystem>
#include <iostream>
#include <print>

#include "iskrac/parser.hpp"
#include "iskrac/visitors/ast_printer.hpp"

int main(int argc, char* argv[]) {
    using namespace iskrac;

    if (argc < 2) {
        std::println(std::cerr, "error: no input files");
        return 1;
    }

    const std::string fileName{ argv[1] };
    if (!std::filesystem::exists(fileName)) {
        std::println(std::cerr, "error: `{}` does not exist", fileName);
        return 1;
    }

    iskrac::SourceText text{ fileName };
    if (!text.isOpen()) {
        std::println(std::cerr, "error: could not open `{}`", fileName);
        return 1;
    }

    ErrorFormatter errfmt{ text };
    StringSpace strings;

    try {
        auto expr = Parser::parse(text, strings, errfmt);

        visitor::ASTPrinter printer{ strings };
        printer.visit(*expr);
    }

    catch (std::exception& e) {
        std::println("{}", e.what());
    }

    return 0;
}
