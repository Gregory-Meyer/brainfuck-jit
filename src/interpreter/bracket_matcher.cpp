#include "interpreter/bracket_matcher.h"

namespace gregjm {
namespace bf {
namespace interpreter {

void BracketMatcher::push_left(const std::size_t left) {
    unmatched_.push(left);
}

void BracketMatcher::push_right(const std::size_t right) {
    const std::size_t left = unmatched_.top();

    if (left >= right) {
        throw std::invalid_argument{ "BracketMatcher::push_right" };
    }

    unmatched_.pop();

    if (bracket_map_.size() <= right) {
        bracket_map_.resize(right + 1);
    }

    bracket_map_[left].type = BracketType::Left;
    bracket_map_[right].type = BracketType::Right;
    bracket_map_[left].match = right;
    bracket_map_[right].match = left;
}

std::optional<std::size_t>
BracketMatcher::match_left(const std::size_t bracket) const noexcept {
    if (bracket >= bracket_map_.size() || !is_left_bracket(bracket)) {
        return std::nullopt;
    }

    return std::make_optional(bracket_map_[bracket].match);
}

std::optional<std::size_t>
BracketMatcher::match_right(const std::size_t bracket) const noexcept {
    if (bracket >= bracket_map_.size() || !is_right_bracket(bracket)) {
        return std::nullopt;
    }

    return std::make_optional(bracket_map_[bracket].match);
}

bool BracketMatcher::is_left_bracket(const std::size_t bracket)
const noexcept {
    return bracket_map_[bracket].type == BracketType::Left;
}

bool BracketMatcher::is_right_bracket(const std::size_t bracket)
const noexcept {
    return bracket_map_[bracket].type == BracketType::Right;
}

} // namespace interpreter
} // namespace bf
} // namespace gregjm
