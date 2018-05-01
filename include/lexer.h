#ifndef GREGJM_BF_LEXER_H
#define GREGJM_BF_LEXER_H

#include "container_types.hpp"
#include "lexer/token.h"

#include <iostream>
#include <memory>
#include <vector>

namespace gregjm {
namespace bf {

class Lexer {
public:
    TokenOwnerContainerT tokenize(std::istream &is);

private:
    TokenOwnerContainerT tokens_;
};

} // namespace bf
} // namespace gregjm

#endif
