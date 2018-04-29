#ifndef GREGJM_BF_LEXER_H
#define GREGJM_BF_LEXER_H

#include "lexer/token.h"

#include <iostream>
#include <memory>
#include <vector>

namespace gregjm {
namespace bf {

class Lexer {
public:
    std::vector<std::unique_ptr<lexer::Token>> tokenize(std::istream &is);

private:
    std::vector<std::unique_ptr<lexer::Token>> tokens_;
};

} // namespace bf
} // namespace gregjm

#endif
