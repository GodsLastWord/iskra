#pragma once

#include <fstream>
#include <string>

#include "tokens.hpp"

namespace iskrac {

class SourceText {
    std::ifstream file;
    const std::string fileName;

public:
    explicit SourceText(const std::string&);

    bool isOpen();
    bool eof();

    std::string name();
    std::string getLineFor(Position);
    std::streampos absoluteCurrentPosition();

    int peek();
    int advance();
};

} // namespace iskrac
