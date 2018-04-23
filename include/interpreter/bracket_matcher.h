#ifndef GREGJM_BF_INTERPRETER_BRACKET_MATCHER_H
#define GREGJM_BF_INTERPRETER_BRACKET_MATCHER_H

#include <cstddef>
#include <limits>
#include <optional>
#include <stack>
#include <stdexcept>
#include <vector>

namespace gregjm {
namespace bf {
namespace interpreter {

class BracketMatcher {
public:
    void push_left(std::size_t left);

    // throws std::invalid_argument if right > most recent left
    void push_right(std::size_t right);

    std::optional<std::size_t> match_left(std::size_t bracket) const noexcept;

    std::optional<std::size_t> match_right(std::size_t bracket) const noexcept;

private:
    bool is_left_bracket(std::size_t bracket) const noexcept;

    bool is_right_bracket(std::size_t bracket) const noexcept;

    enum class BracketType {
        Left,
        Right,
        Unknown
    };

    struct BracketPair {
        BracketType type = BracketType::Unknown;
        std::size_t match = std::numeric_limits<std::size_t>::max();
    };

    std::vector<BracketPair> bracket_map_;
    std::stack<std::size_t, std::vector<std::size_t>> unmatched_;
};

} // namespace interpreter
} // namespace bf
} // namespace gregjm

#endif
