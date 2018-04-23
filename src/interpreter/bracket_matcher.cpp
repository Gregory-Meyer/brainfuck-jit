#include "interpreter/bracket_matcher.h"

namespace gregjm {
namespace bf {
namespace interpreter {
namespace bracket_matcher {

Bracket Bracket::Left(const std::size_t match) noexcept {
    return Bracket{ LeftBracket{ match } };
}

Bracket Bracket::Right(const std::size_t match) noexcept {
    return Bracket{ RightBracket{ match } };
}

bool Bracket::is_left_bracket() const noexcept {
    return data_.index() == 1;
}

bool Bracket::is_right_bracket() const noexcept {
    return data_.index() == 2;
}

BracketType Bracket::type() const noexcept {
    switch (data_.index()) {
    case 0: {
        return BracketType::Unknown;
    }
    case 1: {
        return BracketType::Left;
    }
    case 2: {
        return BracketType::Right;
    }
    default: {
        __builtin_unreachable();
    }
    }
}

std::optional<std::size_t> Bracket::get_left_match() const noexcept {
    if (!is_left_bracket()) {
        return std::nullopt;
    }

    return std::make_optional(std::get<LeftBracket>(data_).match);
}

std::optional<std::size_t> Bracket::get_right_match() const noexcept {
    if (!is_right_bracket()) {
        return std::nullopt;
    }

    return std::make_optional(std::get<RightBracket>(data_).match);
}

Bracket::Bracket(const LeftBracket bracket) noexcept : data_{ bracket } { }

Bracket::Bracket(const RightBracket bracket) noexcept : data_{ bracket } { }

} // namespace bracket_matcher

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

    bracket_map_[left] = bracket_matcher::Bracket::Left(right);
    bracket_map_[right] = bracket_matcher::Bracket::Right(left);
}

std::optional<std::size_t>
BracketMatcher::match_left(const std::size_t bracket) const noexcept {
    if (!is_in_map(bracket)) {
        return std::nullopt;
    }

    return bracket_map_[bracket].get_left_match();
}

std::optional<std::size_t>
BracketMatcher::match_right(const std::size_t bracket) const noexcept {
    if (!is_in_map(bracket)) {
        return std::nullopt;
    }

    return bracket_map_[bracket].get_right_match();
}

bool BracketMatcher::is_in_map(const std::size_t bracket) const noexcept {
    return bracket < bracket_map_.size();
}

} // namespace interpreter
} // namespace bf
} // namespace gregjm
