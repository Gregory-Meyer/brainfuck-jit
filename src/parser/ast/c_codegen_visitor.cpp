#include "parser/ast/c_codegen_visitor.h"

#include <cassert>
#include <string>
#include <string_view>

namespace gregjm::bf::parser::ast {
namespace detail {

std::ostream& insert_spaces(std::ostream &os, const std::intmax_t num_spaces) {
    // likely to be overkill
    const std::string buffer(static_cast<std::size_t>(num_spaces), ' ');

    return os << buffer;
}

} // namespace detail

CCodegenVisitor::CCodegenVisitor(std::ostream &os) noexcept : os_{ &os } { }

void CCodegenVisitor::previsit_body(const BodyNode&) { }

void CCodegenVisitor::postvisit_body(const BodyNode&) { }

void CCodegenVisitor::previsit_main(const MainNode&) {
    static constexpr std::string_view PREVISIT_MAIN_STRING =
        "#include <stdio.h>\n"
        "\n"
        "static char data[30000] = { 0 };\n"
        "static char *ptr = data;\n"
        "\n"
        "int main(void) {\n";

    os() << PREVISIT_MAIN_STRING;
    ++indent_level_;
}

void CCodegenVisitor::postvisit_main(const MainNode&) {
    static constexpr std::string_view POSTVISIT_MAIN_STRING =
        "}\n";

    os() << POSTVISIT_MAIN_STRING;
    --indent_level_;
}

void CCodegenVisitor::do_visit_increment_ptr(const IncrementPointerNode&) {
    os() << "++ptr;\n";
}

void CCodegenVisitor::do_visit_decrement_ptr(const DecrementPointerNode&) {
    os() << "--ptr;\n";
}

void CCodegenVisitor::do_visit_increment_data(const IncrementDataNode&) {
    os() << "++*ptr;\n";
}

void CCodegenVisitor::do_visit_decrement_data(const DecrementDataNode&) {
    os() << "--*ptr;\n";
}

void CCodegenVisitor::do_visit_output_cell(const OutputCellNode&) {
    os() << "putchar(*ptr);\n";
}

void CCodegenVisitor::do_visit_input_cell(const InputCellNode&) {
    os() << "*ptr = (char) getchar();\n";
}

void CCodegenVisitor::previsit_loop(const LoopNode&) {
    os() << "while (*ptr) {\n";
    ++indent_level_;
}

void CCodegenVisitor::postvisit_loop(const LoopNode&) {
    --indent_level_;
    os() << "}\n";
}

std::ostream& CCodegenVisitor::os() noexcept {
    static constexpr std::intmax_t SPACES_PER_INDENT = 4;

    assert(indent_level_ >= 0);

    return detail::insert_spaces(*os_, indent_level_ * SPACES_PER_INDENT);
}

} // namespace gregjm::bf::parser::ast
