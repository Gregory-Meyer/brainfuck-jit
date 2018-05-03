#ifndef GREGJM_BF_PARSER_ABSTRACT_SYNTAX_TREE_H
#define GREGJM_BF_PARSER_ABSTRACT_SYNTAX_TREE_H

#include "container_types.hpp"
#include "lexer/token.h"
#include "parser/ast/node.h"
#include "parser/ast/node_visitor.h"

#include <functional>
#include <memory>
#include <vector>

namespace gregjm {
namespace bf {
namespace parser {

class AbstractSyntaxTree {
public:
    AbstractSyntaxTree(const TokenRefContainerT &tokens);

    void visit(ast::NodeVisitor &visitor) const;

private:
    ast::NodeOwnerT root_;
};

}
}
}

#endif
