#pragma once

#include <format>
#include <iostream>
#include <print>

#include "source_text.hpp"
#include "tokens.hpp"

namespace iskrac {

class ErrorFormatter {
    SourceText& source;

    bool errors{ false };

public:
    explicit ErrorFormatter(SourceText& source)
        : source{ source } {
    }

    inline bool hadErrors() {
        return errors;
    }

    template<typename... Arguments>
    void error(const Token& errorToken, std::format_string<Arguments...> message, Arguments&&... args) {
        std::println(
            std::cerr,
            "{}:[{}, {}]:error: {}\n{:>5} | {}\n",
            source.name(),
            errorToken.position.line,
            errorToken.position.column,
            std::format(message, std::forward<Arguments>(args)...),
            errorToken.position.line,
            source.getLineFor(errorToken.position)
        );
    }
};

} // namespace iskrac
