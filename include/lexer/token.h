#ifndef GREGJM_BF_LEXER_TOKEN_H
#define GREGJM_BF_LEXER_TOKEN_H

#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

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

std::ostream& operator<<(std::ostream &os, const Token &token);

class TokenFactory {
public:
    std::vector<std::unique_ptr<Token>> make_tokens(char maybe_command);

private:
    std::string comment_buffer_;
    std::size_t line_number_ = 1;
};

namespace token {

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

class IncrementPointer : public Token {
public:
    explicit IncrementPointer(std::size_t line) noexcept;

    virtual ~IncrementPointer() = default;

    std::ostream& print(std::ostream &os) const override;
};

class DecrementPointer : public Token {
public:
    explicit DecrementPointer(std::size_t line) noexcept;

    virtual ~DecrementPointer() = default;

    std::ostream& print(std::ostream &os) const override;
};

class IncrementData : public Token {
public:
    explicit IncrementData(std::size_t line) noexcept;

    virtual ~IncrementData() = default;

    std::ostream& print(std::ostream &os) const override;
};

class DecrementData : public Token {
public:
    explicit DecrementData(std::size_t line) noexcept;

    virtual ~DecrementData() = default;

    std::ostream& print(std::ostream &os) const override;
};

class OutputCell : public Token {
public:
    explicit OutputCell(std::size_t line) noexcept;

    virtual ~OutputCell() = default;

    std::ostream& print(std::ostream &os) const override;
};

class InputCell : public Token {
public:
    explicit InputCell(std::size_t line) noexcept;

    virtual ~InputCell() = default;

    std::ostream& print(std::ostream &os) const override;
};

class LoopBegin : public Token {
public:
    explicit LoopBegin(std::size_t line) noexcept;

    virtual ~LoopBegin() = default;

    std::ostream& print(std::ostream &os) const override;
};

class LoopEnd : public Token {
public:
    explicit LoopEnd(std::size_t line) noexcept;

    virtual ~LoopEnd() = default;

    std::ostream& print(std::ostream &os) const override;
};

class Comment : public Token {
public:
    Comment(std::size_t line, std::string_view comment);

    Comment(std::size_t line, std::string &&comment) noexcept;

    virtual ~Comment() = default;

    std::ostream& print(std::ostream &os) const override;

    std::string_view comment() const noexcept;

private:
    std::string comment_;
};

} // namespace token
} // namespace lexer
} // namespace bf
} // namespace gregjm

#endif
