#pragma once
#include <vector>
#include <string>
#include "token.h"

namespace parser {

std::vector<Token> tokenize(const std::string& html);

}
