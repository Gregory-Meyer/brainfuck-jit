#include "parser/ast/node.h"

#include "parser/ast/node_visitor.h"

#include <stdexcept>
#include <utility>

#include <range/v3/view.hpp>

namespace gregjm {
namespace bf {
namespace parser {
namespace ast {
namespace detail {

// gsl::not_null doesn't work with unique_ptr unfortunately
static NodeRefT as_reference(const NodeOwnerT &owner) {
    if (!owner) {
        throw std::invalid_argument{ "detail::as_reference" };
    }

    return *owner;
}

} // namespace detail

void EmptyNode::accept(NodeVisitor &visitor) const {
    visitor.visit_empty(*this);
}

BodyNode::BodyNode(NodeOwnerContainerT &&owners) noexcept
: nodes_{ std::move(owners) } { }

void BodyNode::accept(NodeVisitor &visitor) const {
    visitor.visit_body(*this);
}

NodeRefContainerT BodyNode::nodes() const noexcept {
    return { nodes_ | ranges::view::transform(&detail::as_reference) };
}

MainNode::MainNode(NodeOwnerT &&body) noexcept : body_{ std::move(body) } { }

void MainNode::accept(NodeVisitor &visitor) const {
    visitor.visit_main(*this);
}

std::optional<NodeRefT> MainNode::body() const noexcept {
    if (!body_) {
       return std::nullopt;
    }

    return { *body_ };
}

void IncrementPointerNode::accept(NodeVisitor &visitor) const {
    visitor.visit_increment_ptr(*this);
}

void DecrementPointerNode::accept(NodeVisitor &visitor) const {
    visitor.visit_decrement_ptr(*this);
}

void OutputCellNode::accept(NodeVisitor &visitor) const {
    visitor.visit_output_cell(*this);
}

void InputCellNode::accept(NodeVisitor &visitor) const {
    visitor.visit_input_cell(*this);
}

LoopNode::LoopNode(NodeOwnerT &&body) noexcept : body_{ std::move(body) } { }

void LoopNode::accept(NodeVisitor &visitor) const {
    visitor.visit_loop(*this);
}

std::optional<NodeRefT> LoopNode::body() const noexcept {
    if (!body_) {
       return std::nullopt;
    }

    return { *body_ };
}

} // namespace ast
} // namespace parser
} // namespace bf
} // namespace gregjm
