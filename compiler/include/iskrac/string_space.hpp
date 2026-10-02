#pragma once

#include <vector>
#include <string>

namespace iskrac {

class StringSpace {
    std::vector<std::string> strs;

public:
    explicit StringSpace();

    std::size_t add(const std::string&);
    std::string get(std::size_t) const;
};

}
