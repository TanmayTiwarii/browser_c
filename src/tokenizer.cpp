#include "tokenizer.h"
#include <cctype>

namespace parser {

static inline std::string trim(const std::string& s) {
    size_t start = 0, end = s.size();
    while (start < end && std::isspace((unsigned char)s[start])) start++;
    while (end > start && std::isspace((unsigned char)s[end - 1])) end--;
    return s.substr(start, end - start);
}

std::vector<Token> tokenize(const std::string& html) {
    std::vector<Token> tokens;
    std::string buffer;
    buffer.reserve(64);

    const size_t n = html.size();

    for (size_t i = 0; i < n; ++i) {
        char c = html[i];

        if (c == '<') {
            std::string text = trim(buffer);
            if (!text.empty()) {
                tokens.push_back({TokenType::Text, text});
            }
            buffer.clear();

            ++i;
            bool closing = false;

            if (i < n && html[i] == '/') {
                closing = true;
                ++i;
            }

            std::string tag;
            while (i < n && html[i] != '>' && !std::isspace((unsigned char)html[i])) {
                tag += html[i++];
            }

            while (i < n && html[i] != '>') ++i;

            if (!tag.empty()) {
                tokens.push_back({
                    closing ? TokenType::TagClose : TokenType::TagOpen,
                    tag
                });
            }
        } else {
            buffer += c;
        }
    }

    std::string text = trim(buffer);
    if (!text.empty()) {
        tokens.push_back({TokenType::Text, text});
    }

    return tokens;
}

} // namespace parser
