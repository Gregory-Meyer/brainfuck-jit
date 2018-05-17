#include "parser/ast/node_visitor.h"

#include "parser/ast/node.h"

#include <iostream>

namespace gregjm {
namespace bf {
namespace parser {
namespace ast {
namespace detail {

#if defined(DEBUG) && !defined(NDEBUG)
static constexpr inline bool SHOULD_LOG = true;
#else
static constexpr inline bool SHOULD_LOG = false;
#endif

} // namespace detail

void NodeVisitor::visit_body(const BodyNode &body) {
    if constexpr (detail::SHOULD_LOG) {
        std::cout << "previsiting body node " << &body << '\n';
    }

    previsit_body(body);

    for (const Node &node : body.nodes()) {
        node.accept(*this);
    }

    if constexpr (detail::SHOULD_LOG) {
        std::cout << "postvisiting body node" << &body << '\n';
    }

    postvisit_body(body);
}

void NodeVisitor::visit_main(const MainNode &main) {
    if constexpr (detail::SHOULD_LOG) {
        std::cout << "previsiting main node " << &main << '\n';
    }

    previsit_main(main);

    if (main.body().has_value()) {
        const Node &body = main.body().value();
        body.accept(*this);
    }

    if constexpr (detail::SHOULD_LOG) {
        std::cout << "postvisiting main node " << &main << '\n';
    }

    postvisit_main(main);
}

void NodeVisitor::visit_increment_ptr(const IncrementPointerNode &inc_ptr) {
    if constexpr (detail::SHOULD_LOG) {
        std::cout << "visiting increment pointer node " << &inc_ptr << '\n';
    }

    do_visit_increment_ptr(inc_ptr);
}

void NodeVisitor::visit_decrement_ptr(const DecrementPointerNode &dec_ptr) {
    if constexpr (detail::SHOULD_LOG) {
        std::cout << "visiting decrement pointer node " << &dec_ptr << '\n';
    }

    do_visit_decrement_ptr(dec_ptr);
}

void NodeVisitor::visit_increment_data(const IncrementDataNode &inc_data) {
    if constexpr (detail::SHOULD_LOG) {
        std::cout << "visiting increment data node " << &inc_data << '\n';
    }

    do_visit_increment_data(inc_data);
}

void NodeVisitor::visit_decrement_data(const DecrementDataNode &dec_data) {
    if constexpr (detail::SHOULD_LOG) {
        std::cout << "visiting decrement data node " << &dec_data << '\n';
    }

    do_visit_decrement_data(dec_data);
}

void NodeVisitor::visit_output_cell(const OutputCellNode &output) {
    if constexpr (detail::SHOULD_LOG) {
        std::cout << "visiting output cell node " << &output << '\n';
    }

    do_visit_output_cell(output);
}

void NodeVisitor::visit_input_cell(const InputCellNode &input) {
    if constexpr (detail::SHOULD_LOG) {
        std::cout << "visiting input cell node " << &input << '\n';
    }

    do_visit_input_cell(input);
}

void NodeVisitor::visit_loop(const LoopNode &loop) {
    if constexpr (detail::SHOULD_LOG) {
        std::cout << "previsiting loop node " << &loop << '\n';
    }

    previsit_loop(loop);

    if (loop.body().has_value()) {
        const Node &body = loop.body().value();
        body.accept(*this);
    }

    if constexpr (detail::SHOULD_LOG) {
        std::cout << "postvisiting loop node " << &loop << '\n';
    }

    postvisit_loop(loop);
}

} // namespace ast
} // namespace parser
} // namespace bf
} // namespace gregjm
