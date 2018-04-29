#ifndef GREGJM_BF_PARSER_AST_NODE_VISITOR_H
#define GREGJM_BF_PARSER_AST_NODE_VISITOR_H

#include "parser/ast/node_fwd.h"

namespace gregjm {
namespace bf {
namespace parser {
namespace ast {

class NodeVisitor {
public:
    virtual void visit_increment_ptr(const IncrementPointerNode &inc_ptr) = 0;

    virtual void visit_decrement_ptr(const DecrementPointerNode &dec_ptr) = 0;

    virtual void visit_increment_data(const IncrementDataNode &inc_data) = 0;

    virtual void visit_decrement_data(const DecrementDataNode &dec_data) = 0;

    virtual void visit_output_cell(const IncrementDataNode &inc_data) = 0;

    virtual void visit_input_cell(const DecrementDataNode &dec_data) = 0;

    virtual void visit_loop(const LoopNode &loop) = 0;
};

class LlvmCodegenVisitor : public NodeVisitor {
    void visit_increment_ptr(const IncrementPointerNode &inc_ptr) override;

    void visit_decrement_ptr(const DecrementPointerNode &dec_ptr) override;

    void visit_increment_data(const IncrementDataNode &inc_data) override;

    void visit_decrement_data(const DecrementDataNode &dec_data) override;

    void visit_output_cell(const IncrementDataNode &inc_data) override;

    void visit_input_cell(const DecrementDataNode &dec_data) override;

    void visit_loop(const LoopNode &loop) override;
};

} // namespace ast
} // namespace parser
} // namespace bf
} // namespace gregjm

#endif
