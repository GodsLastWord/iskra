#include "iskra/source_text.hpp"

namespace iskrac {

SourceText::SourceText(const std::string& fileName)
    : file{ fileName, std::ios::binary }
    , fileName{ fileName } {
}

bool SourceText::isOpen() {
    return file.is_open();
}

bool SourceText::eof() {
    return file.eof();
}

std::string SourceText::name() {
    return fileName;
} 

int SourceText::peek() {
    return file.peek();
}

int SourceText::advance() {
    return file.get();
}

} // namespace iskrac
