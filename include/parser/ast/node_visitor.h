#ifndef GREGJM_BF_PARSER_AST_NODE_VISITOR_H
#define GREGJM_BF_PARSER_AST_NODE_VISITOR_H

#include "parser/ast/node_fwd.h"
#include "parser/ast/node_visitor_fwd.h"

#include <iostream>

#include <gsl/gsl>

namespace gregjm {
namespace bf {
namespace parser {
namespace ast {

class NodeVisitor {
public:
    virtual void visit_empty(const EmptyNode &empty) = 0;

    virtual void visit_body(const BodyNode &body) = 0;

    virtual void visit_main(const MainNode &main) = 0;

    virtual void visit_increment_ptr(const IncrementPointerNode &inc_ptr) = 0;

    virtual void visit_decrement_ptr(const DecrementPointerNode &dec_ptr) = 0;

    virtual void visit_increment_data(const IncrementDataNode &inc_data) = 0;

    virtual void visit_decrement_data(const DecrementDataNode &dec_data) = 0;

    virtual void visit_output_cell(const OutputCellNode &output) = 0;

    virtual void visit_input_cell(const InputCellNode &input) = 0;

    virtual void visit_loop(const LoopNode &loop) = 0;
};

class DebugVisitor : public NodeVisitor {
public:
    DebugVisitor(NodeVisitor &parent, std::ostream &logger) noexcept;

    void visit_empty(const EmptyNode &empty) override;

    void visit_body(const BodyNode &body) override;

    void visit_main(const MainNode &main) override;

    void visit_increment_ptr(const IncrementPointerNode &inc_ptr) override;

    void visit_decrement_ptr(const DecrementPointerNode &dec_ptr) override;

    void visit_increment_data(const IncrementDataNode &inc_data) override;

    void visit_decrement_data(const DecrementDataNode &dec_data) override;

    void visit_output_cell(const OutputCellNode &output) override;

    void visit_input_cell(const InputCellNode &input) override;

    void visit_loop(const LoopNode &loop) override;

private:
    NodeVisitor& parent() noexcept;

    std::ostream& logger() const noexcept;

    gsl::not_null<NodeVisitor*> parent_;
    gsl::not_null<std::ostream*> logger_;
};

} // namespace ast
} // namespace parser
} // namespace bf
} // namespace gregjm

#endif
