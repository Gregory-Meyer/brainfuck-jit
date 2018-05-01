#ifndef GREGJM_BF_PARSER_ABSTRACT_SYNTAX_TREE_H
#define GREGJM_BF_PARSER_ABSTRACT_SYNTAX_TREE_H

#include "container_types.hpp"
#include "lexer/token.h"
#include "parser/ast/node.h"

#include <functional>
#include <memory>
#include <vector>

namespace gregjm {
namespace bf {
namespace parser {

class AbstractSyntaxTree {
public:
    AbstractSyntaxTree(const TokenRefContainerT &tokens);

private:
    std::unique_ptr<ast::Node> root_;
};

}
}
}

#endif
