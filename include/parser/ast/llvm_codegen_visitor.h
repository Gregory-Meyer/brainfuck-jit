#ifndef GREGJM_BF_PARSER_AST_LLVM_CODEGEN_VISITOR_H
#define GREGJM_BF_PARSER_AST_LLVM_CODEGEN_VISITOR_H

#include "parser/ast/node_visitor.h"

namespace gregjm {
namespace bf {
namespace parser {
namespace ast {

class LlvmCodegenVisitor : public NodeVisitor {
public:
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
    
};

} // namespace ast 
} // namespace parser
} // namespace bf
} // namespace gregjm

#endif
