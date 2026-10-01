#include <print>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "iskra/source_text.hpp"

int main(int argc, char* argv[]) {
    
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

    std::stringstream buf;
    for (int c = text.advance(); !text.eof(); c = text.advance()) {
        buf << static_cast<char>(c);
    }

    std::println("```\n{}```", buf.str());

    return 0;
}
