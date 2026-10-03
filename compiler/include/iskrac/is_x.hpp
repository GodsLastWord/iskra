#pragma once

#include <string>

namespace iskrac {

bool isDigit(int);
bool isOperator(int);
bool isOperator(const std::string&);
bool isBracket(int);
bool isBracket(const std::string&);
bool isSpace(int);

bool isValidInt32Literal(const std::string&);

}
