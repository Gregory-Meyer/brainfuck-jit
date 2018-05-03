#ifndef GREGJM_BF_PARSER_AST_NODE_H
#define GREGJM_BF_PARSER_AST_NODE_H

#include "parser/ast/node_visitor_fwd.h"
#include "parser/ast/node_fwd.h"

#include <memory>
#include <optional>
#include <vector>

#include <gsl/gsl>

namespace gregjm {
namespace bf {
namespace parser {
namespace ast {

using NodeRefT = std::reference_wrapper<const Node>;
using NodeOwnerT = std::unique_ptr<Node>;
using NodeRefContainerT = std::vector<NodeRefT>;
using NodeOwnerContainerT = std::vector<NodeOwnerT>;

class Node {
public:
    virtual ~Node() = 0;

    virtual void accept(NodeVisitor &visitor) const = 0;
};

class EmptyNode : public Node {
public:
    virtual ~EmptyNode() = default;

    void accept(NodeVisitor &visitor) const override;
};

class BodyNode : public Node {
public:
    BodyNode(NodeOwnerContainerT &&owners) noexcept;

    virtual ~BodyNode() = default;

    void accept(NodeVisitor &visitor) const override;

    NodeRefContainerT nodes() const noexcept;

private:
    NodeOwnerContainerT nodes_;
};

class MainNode : public Node {
public:
    MainNode(NodeOwnerT &&body) noexcept;

    virtual ~MainNode() = default;

    void accept(NodeVisitor &visitor) const override;

    std::optional<NodeRefT> body() const noexcept;

private:
    NodeOwnerT body_;
};

class IncrementPointerNode : public Node {
public:
    virtual ~IncrementPointerNode() = default;

    void accept(NodeVisitor &visitor) const override;
};

class DecrementPointerNode : public Node {
public:
    virtual ~DecrementPointerNode() = default;

    void accept(NodeVisitor &visitor) const override;
};

class IncrementDataNode : public Node {
public:
    virtual ~IncrementDataNode() = default;

    void accept(NodeVisitor &visitor) const override;
};

class DecrementDataNode : public Node {
public:
    virtual ~DecrementDataNode() = default;

    void accept(NodeVisitor &visitor) const override;
};

class OutputCellNode : public Node {
public:
    virtual ~OutputCellNode() = default;

    void accept(NodeVisitor &visitor) const override;
};

class InputCellNode : public Node {
public:
    virtual ~InputCellNode() = default;

    void accept(NodeVisitor &visitor) const override;
};

class LoopNode : public Node {
public:
    LoopNode(NodeOwnerT &&body) noexcept;

    virtual ~LoopNode() = default; 

    void accept(NodeVisitor &visitor) const override;

    std::optional<NodeRefT> body() const noexcept;

private:
    NodeOwnerT body_;
};

} // namespace ast
} // namespace parser
} // namespace bf
} // namespace gregjm

#endif
