#include "parser.h"

#include <iostream>

#include <range/v3/action.hpp>

namespace gregjm {
namespace bf {
namespace detail {

static bool is_comment(const lexer::Token &token) {
    try {
        [[maybe_unused]] const auto &comment =
            dynamic_cast<const lexer::token::Comment&>(token);

        return true;
    } catch (const std::bad_cast &e) {
        return false;
    }
}

} // namespace detail

Parser::Parser(TokenRefContainerT tokens) noexcept
: tokens_{ std::move(tokens) | ranges::action::remove_if(&detail::is_comment) },
  tree_{ tokens_ } { }

parser::AbstractSyntaxTree Parser::build_tree() {
    return std::move(tree_);
}

} // namespace bf
} // namespace gregjm
