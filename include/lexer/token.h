#ifndef GREGJM_BF_LEXER_TOKEN_H
#define GREGJM_BF_LEXER_TOKEN_H

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <variant>

namespace gregjm {
namespace bf {
namespace lexer {
namespace token {

struct IncrementPointer { };

struct DecrementPointer { };

struct IncrementData { };

struct DecrementData { };

struct OutputCell { };

struct InputCell { };

struct LoopBegin { };

struct LoopEnd { };

struct Comment {
    Comment(const std::string_view comment) : data{ comment } { }

    Comment(std::string &&comment) noexcept
    : data{ std::move(comment) } { }

    std::string data;
};

} // namespace token

enum class TokenType {
    IncrementPointer,
    DecrementPointer,
    IncrementData,
    DecrementData,
    OutputCell,
    InputCell,
    LoopBegin,
    LoopEnd,
    Comment
};

class Token {
public:
    Token(std::size_t line, token::IncrementPointer token) noexcept;

    Token(std::size_t line, token::DecrementPointer token) noexcept;

    Token(std::size_t line, token::IncrementData token) noexcept;

    Token(std::size_t line, token::DecrementData token) noexcept;

    Token(std::size_t line, token::OutputCell token) noexcept;

    Token(std::size_t line, token::InputCell token) noexcept;

    Token(std::size_t line, token::LoopBegin token) noexcept;

    Token(std::size_t line, token::LoopEnd token) noexcept;

    Token(std::size_t line, token::Comment token) noexcept;

    TokenType type() const noexcept;

    std::size_t line() const noexcept;

    std::optional<std::string_view> comment() const noexcept;

private:
    std::variant<token::IncrementPointer, token::DecrementPointer,
                 token::IncrementData, token::DecrementData,
                 token::OutputCell, token::InputCell,
                 token::LoopBegin, token::LoopEnd,
                 token::Comment> data_;
    std::size_t line_number_;
};

} // namespace lexer
} // namespace bf
} // namespace gregjm

#endif
