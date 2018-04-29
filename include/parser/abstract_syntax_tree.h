#ifndef GREGJM_BF_PARSER_ABSTRACT_SYNTAX_TREE_H
#define GREGJM_BF_PARSER_ABSTRACT_SYNTAX_TREE_H

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
    AbstractSyntaxTree(
        const std::vector<std::reference_wrapper<lexer::Token>> &tokens
    );
private:
    std::unique_ptr<ast::Node> root_;
};

}
}
}

#endif
