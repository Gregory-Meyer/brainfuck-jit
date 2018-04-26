#include "lexer.h"

#include <optional>
#include <utility>

namespace gregjm {
namespace bf {
namespace detail {

static std::optional<lexer::Token>
classify_token(const char maybe_token) noexcept {
    switch (maybe_token) {
    case '>': return std::make_optional(lexer::Token::IncrementPointer);
    case '<': return std::make_optional(lexer::Token::DecrementPointer);
    case '+': return std::make_optional(lexer::Token::IncrementData);
    case '-': return std::make_optional(lexer::Token::DecrementData);
    case '.': return std::make_optional(lexer::Token::OutputCell);
    case ',': return std::make_optional(lexer::Token::InputCell);
    case '[': return std::make_optional(lexer::Token::LoopBegin);
    case ']': return std::make_optional(lexer::Token::LoopEnd);
    default: return std::nullopt;
    }
}

} // namespace detail

std::vector<lexer::Token> Lexer::tokenize(std::istream &is) {
    const std::string buffer = [&is] {
        const std::istreambuf_iterator<char> first{ is };
        const std::istreambuf_iterator<char> last;

        const std::string buf(first, last);

        return buf;
    }();

    tokens_.reserve(buffer.size());

    for (const char maybe_token : buffer) {
        const auto token = detail::classify_token(maybe_token);

        if (token.has_value()) {
            tokens_.push_back(token.value());
        }
    }

    return std::move(tokens_);
}

} // namespace bf
} // namespace gregjm
