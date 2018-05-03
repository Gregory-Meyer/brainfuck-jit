#include "parser/ast/node_visitor.h"

namespace gregjm {
namespace bf {
namespace parser {
namespace ast {

DebugVisitor::DebugVisitor(NodeVisitor &parent, std::ostream &logger) noexcept
: parent_{ &parent }, logger_{ &logger } { }

void DebugVisitor::visit_empty(const EmptyNode &empty) {
    logger() << "visiting empty node\n";
    parent().visit_empty(empty);
}

void DebugVisitor::visit_body(const BodyNode &body) {
    logger() << "visiting body node\n";
    parent().visit_body(body);
}

void DebugVisitor::visit_main(const MainNode &main) {
    logger() << "visiting main node\n";
    parent().visit_main(main);
}

void DebugVisitor::visit_increment_ptr(const IncrementPointerNode &inc_ptr) {
    logger() << "visiting increment pointer node\n";
    parent().visit_increment_ptr(inc_ptr);
}

void DebugVisitor::visit_decrement_ptr(const DecrementPointerNode &dec_ptr) {
    logger() << "visiting decrement pointer node\n";
    parent().visit_decrement_ptr(dec_ptr);
}

void DebugVisitor::visit_increment_data(const IncrementDataNode &inc_data) {
    logger() << "visiting increment data node\n";
    parent().visit_increment_data(inc_data);
}

void DebugVisitor::visit_decrement_data(const DecrementDataNode &dec_data) {
    logger() << "visiting decrement data node\n";
    parent().visit_decrement_data(dec_data);
}

void DebugVisitor::visit_output_cell(const OutputCellNode &output) {
    logger() << "visiting output cell node\n";
    parent().visit_output_cell(output);
}

void DebugVisitor::visit_input_cell(const InputCellNode &input) {
    logger() << "visiting input cell node\n";
    parent().visit_input_cell(input);
}

void DebugVisitor::visit_loop(const LoopNode &loop) {
    logger() << "visiting loop node\n";
    parent().visit_loop(loop);
}

NodeVisitor& DebugVisitor::parent() noexcept {
    return *parent_;
}

std::ostream& DebugVisitor::logger() const noexcept {
    return *logger_;
}

} // namespace ast
} // namespace parser
} // namespace bf
} // namespace gregjm
