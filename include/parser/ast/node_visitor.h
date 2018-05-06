#ifndef GREGJM_BF_PARSER_AST_NODE_VISITOR_H
#define GREGJM_BF_PARSER_AST_NODE_VISITOR_H

#include "parser/ast/node_fwd.h"
#include "parser/ast/node_visitor_fwd.h"

namespace gregjm {
namespace bf {
namespace parser {
namespace ast {

class NodeVisitor {
public:
    void visit_body(const BodyNode &body);

    void visit_main(const MainNode &main);

    void visit_increment_ptr(const IncrementPointerNode &inc_ptr);

    void visit_decrement_ptr(const DecrementPointerNode &dec_ptr);

    void visit_increment_data(const IncrementDataNode &inc_data);

    void visit_decrement_data(const DecrementDataNode &dec_data);

    void visit_output_cell(const OutputCellNode &output);

    void visit_input_cell(const InputCellNode &input);

    void visit_loop(const LoopNode &loop);

private:
    virtual void previsit_body(const BodyNode &body) = 0;

    virtual void postvisit_body(const BodyNode &body) = 0;

    virtual void previsit_main(const MainNode &main) = 0;

    virtual void postvisit_main(const MainNode &main) = 0;

    virtual void do_visit_increment_ptr(
        const IncrementPointerNode &inc_ptr
    ) = 0;

    virtual void do_visit_decrement_ptr(
        const DecrementPointerNode &dec_ptr
    ) = 0;

    virtual void do_visit_increment_data(
        const IncrementDataNode &inc_data
    ) = 0;

    virtual void do_visit_decrement_data(
        const DecrementDataNode &dec_data
    ) = 0;

    virtual void do_visit_output_cell(const OutputCellNode &output) = 0;

    virtual void do_visit_input_cell(const InputCellNode &input) = 0;

    virtual void previsit_loop(const LoopNode &loop) = 0;

    virtual void postvisit_loop(const LoopNode &loop) = 0;
};

} // namespace ast
} // namespace parser
} // namespace bf
} // namespace gregjm

#endif
