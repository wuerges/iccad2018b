#pragma once

#include <input.hpp>
#include <optional>

namespace parser {
    std::optional<Input> parse_file(char* filename);
}