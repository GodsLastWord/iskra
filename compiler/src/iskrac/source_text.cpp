#include "iskrac/source_text.hpp"

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

std::string SourceText::getLineFor(Position position) {
    std::ios::iostate currentState = file.rdstate();
    file.clear();

    std::streampos currentPosition = file.tellg();
    file.seekg(position.lastLineStart);

    std::string line;
    std::getline(file, line);
    
    file.seekg(currentPosition);
    file.setstate(currentState);

    return line;
}

int SourceText::peek() {
    return file.peek();
}

int SourceText::advance() {
    return file.get();
}

} // namespace iskrac
