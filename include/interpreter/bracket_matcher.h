#ifndef GREGJM_BF_INTERPRETER_BRACKET_MATCHER_H
#define GREGJM_BF_INTERPRETER_BRACKET_MATCHER_H

#include <cstddef>
#include <limits>
#include <optional>
#include <stack>
#include <stdexcept>
#include <vector>
#include <variant>

namespace gregjm {
namespace bf {
namespace interpreter {
namespace bracket_matcher {

enum class BracketType {
    Left,
    Right,
    Unknown
};

class Bracket {
public:
    Bracket() = default;

    static Bracket Left(std::size_t match) noexcept;

    static Bracket Right(std::size_t match) noexcept;

    bool is_left_bracket() const noexcept;

    bool is_right_bracket() const noexcept;

    BracketType type() const noexcept;

    std::optional<std::size_t> get_left_match() const noexcept;

    std::optional<std::size_t> get_right_match() const noexcept;

private:
    struct LeftBracket {
        std::size_t match;
    };

    struct RightBracket {
        std::size_t match;
    };

    struct NotBracket { };

    Bracket(LeftBracket bracket) noexcept;

    Bracket(RightBracket bracket) noexcept;

    std::variant<NotBracket, LeftBracket, RightBracket> data_ = NotBracket{ };
};

} // namespace bracket_matcher

class BracketMatcher {
public:
    void push_left(std::size_t left);

    // throws std::invalid_argument if right > most recent left
    void push_right(std::size_t right);

    std::optional<std::size_t> match_left(std::size_t bracket) const noexcept;

    std::optional<std::size_t> match_right(std::size_t bracket) const noexcept;

private:
    bool is_in_map(std::size_t bracket) const noexcept;

    std::vector<bracket_matcher::Bracket> bracket_map_;
    std::stack<std::size_t, std::vector<std::size_t>> unmatched_;
};

} // namespace interpreter
} // namespace bf
} // namespace gregjm

#endif
