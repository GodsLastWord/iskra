#include "iskrac/string_space.hpp"

#include <algorithm>
#include <format>
#include <stdexcept>

namespace iskrac {

StringSpace::StringSpace() {
    add("");
}

std::size_t StringSpace::add(const std::string& lexeme) {
    auto it = std::find(strs.begin(), strs.end(), lexeme);

    if (it != strs.end()) {
        return it - strs.begin();
    }

    strs.push_back(lexeme);
    return strs.size() - 1;
}

std::string StringSpace::get(std::size_t index) const {
    if (index >= strs.size()) {
        throw std::runtime_error(
            std::format(
                "iskrac::StringSpace::get: no such index: index >= strs.size() ({} >= {})",
                index,
                strs.size()
            )
        );
    }

    return strs[index];
}

} // namespace iskrac
