#ifndef GREGJM_BF_LEXER_TOKEN_H
#define GREGJM_BF_LEXER_TOKEN_H

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>

namespace gregjm {
namespace bf {
namespace lexer {

class Token {
public:
    virtual std::ostream& print(std::ostream &os) const = 0;

    virtual ~Token() = default;

    std::size_t line() const noexcept;

protected:
    explicit Token(std::size_t line) noexcept;

private:
    std::size_t line_number_;
};

using TokenOwnerT = std::unique_ptr<Token>;

std::ostream& operator<<(std::ostream &os, const Token &token);

std::istream& operator>>(std::istream &is, TokenOwnerT &token);

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

class IncrementPointerToken : public Token {
public:
    explicit IncrementPointerToken(std::size_t line) noexcept;

    virtual ~IncrementPointerToken() = default;

    std::ostream& print(std::ostream &os) const override;
};

class DecrementPointerToken : public Token {
public:
    explicit DecrementPointerToken(std::size_t line) noexcept;

    virtual ~DecrementPointerToken() = default;

    std::ostream& print(std::ostream &os) const override;
};

class IncrementDataToken : public Token {
public:
    explicit IncrementDataToken(std::size_t line) noexcept;

    virtual ~IncrementDataToken() = default;

    std::ostream& print(std::ostream &os) const override;
};

class DecrementDataToken : public Token {
public:
    explicit DecrementDataToken(std::size_t line) noexcept;

    virtual ~DecrementDataToken() = default;

    std::ostream& print(std::ostream &os) const override;
};

class OutputCellToken : public Token {
public:
    explicit OutputCellToken(std::size_t line) noexcept;

    virtual ~OutputCellToken() = default;

    std::ostream& print(std::ostream &os) const override;
};

class InputCellToken : public Token {
public:
    explicit InputCellToken(std::size_t line) noexcept;

    virtual ~InputCellToken() = default;

    std::ostream& print(std::ostream &os) const override;
};

class LoopBeginToken : public Token {
public:
    explicit LoopBeginToken(std::size_t line) noexcept;

    virtual ~LoopBeginToken() = default;

    std::ostream& print(std::ostream &os) const override;
};

class LoopEndToken : public Token {
public:
    explicit LoopEndToken(std::size_t line) noexcept;

    virtual ~LoopEndToken() = default;

    std::ostream& print(std::ostream &os) const override;
};

class CommentToken : public Token {
public:
    CommentToken(std::size_t line, std::string_view comment);

    CommentToken(std::size_t line, std::string &&comment) noexcept;

    virtual ~CommentToken() = default;

    std::ostream& print(std::ostream &os) const override;

    std::string_view comment() const noexcept;

private:
    std::string comment_;
};

} // namespace lexer
} // namespace bf
} // namespace gregjm

#endif
