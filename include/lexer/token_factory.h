#ifndef GREGJM_BF_LEXER_TOKEN_FACTORY_H
#define GREGJM_BF_LEXER_TOKEN_FACTORY_H

#include "container_types.hpp"
#include "lexer/token.h"

#include <cstddef>
#include <string>

namespace gregjm {
namespace bf {
namespace lexer {

class TokenFactory {
public:
    TokenOwnerContainerT make_tokens(char maybe_command);

private:
    std::string comment_buffer_;
    std::size_t line_number_ = 1;
};

} // namespace lexer
} // namespace bf
} // namespace gregjm

#endif
