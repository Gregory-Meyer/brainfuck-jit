#ifndef GREGJM_BF_PARSER_H
#define GREGJM_BF_PARSER_H

#include "container_types.hpp"
#include "lexer/token.h"
#include "parser/abstract_syntax_tree.h"

namespace gregjm {
namespace bf {

class Parser {
public:
    Parser(TokenRefContainerT tokens) noexcept;

    parser::AbstractSyntaxTree build_tree();
    
private:
    TokenRefContainerT tokens_;
    parser::AbstractSyntaxTree tree_;
};

} // namespace bf
} // namespace gregjm

#endif
