#ifndef GREGJM_BF_PARSER_AST_C_CODEGEN_VISITOR_H
#define GREGJM_BF_PARSER_AST_C_CODEGEN_VISITOR_H

#include "parser/ast/node_visitor.h"

#include <cstdint>

#include <gsl/gsl>

namespace gregjm::bf::parser::ast {

class CCodegenVisitor : public NodeVisitor {
    CCodegenVisitor(std::ostream &os) noexcept;

private:
    void previsit_body(const BodyNode &body) override;

    void postvisit_body(const BodyNode &body) override;

    void previsit_main(const MainNode &main) override;

    void postvisit_main(const MainNode &main) override;

    void do_visit_increment_ptr(const IncrementPointerNode &inc_ptr) override;

    void do_visit_decrement_ptr(const DecrementPointerNode &dec_ptr) override;

    void do_visit_increment_data(const IncrementDataNode &inc_data) override;

    void do_visit_decrement_data(const DecrementDataNode &dec_data) override;

    void do_visit_output_cell(const OutputCellNode &output) override;

    void do_visit_input_cell(const InputCellNode &input) override;

    void previsit_loop(const LoopNode &loop) override;

    void postvisit_loop(const LoopNode &loop) override;

    // returns a reference to the ostream passed in at construction, inserting
    // the number of indents as required
    std::ostream& os() noexcept;

    std::intmax_t indent_level_ = 0;
    gsl::not_null<std::ostream*> os_;
};

} // namespace gregjm::bf::parser::ast

#endif
