#pragma once

#include <fstream>
#include <string>

namespace iskrac {

class SourceText {
    std::ifstream file;
    const std::string fileName;

public:
    explicit SourceText(const std::string&);

    bool isOpen();
    bool eof();

    std::string name();

    int peek();
    int advance();
};

} // namespace iskrac
