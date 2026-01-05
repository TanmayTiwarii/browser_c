#pragma once
#include <string>

namespace parser {

enum class TokenType {
    TagOpen,
    TagClose,
    Text
};

struct Token {
    TokenType type;
    std::string value;
};

} // namespace parser
