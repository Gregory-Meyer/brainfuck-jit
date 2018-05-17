#include "parser/abstract_syntax_tree.h"

namespace gregjm {
namespace bf {
namespace parser {

AbstractSyntaxTree::AbstractSyntaxTree(const TokenRefContainerT &tokens) {
    
}

void AbstractSyntaxTree::visit(ast::NodeVisitor &visitor) const {
    if (!root_) {
        return;
    }

    root_->accept(visitor);
}

} // namespace parser
} // namespace bf
} // namespace gregjm
