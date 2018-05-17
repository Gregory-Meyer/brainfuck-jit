#ifndef GREGJM_BF_PARSER_AST_LLVM_CODEGEN_VISITOR_H
#define GREGJM_BF_PARSER_AST_LLVM_CODEGEN_VISITOR_H

#include "parser/ast/node_visitor.h"

#include <memory>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

namespace gregjm {
namespace bf {
namespace parser {
namespace ast {

class LlvmCodegenVisitor : public NodeVisitor {
public:
    LlvmCodegenVisitor();

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

    llvm::LLVMContext context_;
    llvm::IRBuilder<> builder_{ context_ };
    std::unique_ptr<llvm::Module> module_;
};

} // namespace ast 
} // namespace parser
} // namespace bf
} // namespace gregjm

#endif
