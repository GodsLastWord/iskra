#pragma once

#include <string>

namespace iskrac {

bool isDigit(int);
bool isOperator(int);
bool isBracket(int);
bool isSpace(int);

bool isValidInt32Literal(const std::string&);

}
