#ifndef GREGJM_BF_LEXER_H
#define GREGJM_BF_LEXER_H

#include "lexer/token.h"

#include <iostream>
#include <variant>
#include <vector>

namespace gregjm {
namespace bf {

class Lexer {
public:
    std::vector<lexer::Token> tokenize(std::istream &is);

private:
    std::vector<lexer::Token> tokens_;
};

} // namespace bf
} // namespace gregjm

#endif
