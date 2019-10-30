#pragma once

#include <optional>
#include <ast.hpp>

namespace parser {
    std::optional<ast::Input> parse_file(const char* filename);
}