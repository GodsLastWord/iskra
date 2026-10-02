#pragma once

#include <map>
#include <string>

#include "tokens.hpp"

namespace iskrac {

extern const std::map<std::string, Token::Kind> OPERATORS;
extern const std::map<std::string, Token::Kind> BRACKETS;

} // namespace iskrac
