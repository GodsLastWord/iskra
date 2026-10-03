#include <filesystem>
#include <iostream>
#include <print>

#include "iskrac/scanner.hpp"

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
    Scanner scan{ text, strings, errfmt };

    try {
        for (Token t = scan.next(); t.kind != Token::Kind::_EOF; t = scan.next()) {
            // std::println(
            //     "{:>5}[{:>3}, {:>3}] -> `{}`",
            //     int(t.kind),
            //     t.position.line,
            //     t.position.column,
            //     strings.get(t.lexeme)
            // );
        }
    }

    catch (std::exception& e) {
        std::println("{}", e.what());
    }

    return 0;
}
