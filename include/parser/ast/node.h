#ifndef GREGJM_BF_PARSER_AST_NODE_H
#define GREGJM_BF_PARSER_AST_NODE_H

#include "parser/ast/node_visitor_fwd.h"

#include <memory>

namespace gregjm {
namespace bf {
namespace parser {
namespace ast {

class Node {
public:
    virtual ~Node() = 0;

    virtual void accept(NodeVisitor &visitor) const = 0;
};

class LoopNode : public Node {
public:
    virtual ~LoopNode() = default; 

    void accept(NodeVisitor &visitor) const override;

private:
};

} // namespace ast
} // namespace parser
} // namespace bf
} // namespace gregjm

#endif
