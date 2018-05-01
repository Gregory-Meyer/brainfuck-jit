#include "lexer/token.h"

#include <utility>

namespace gregjm {
namespace bf {
namespace lexer {

Token::Token(const std::size_t line) noexcept : line_number_{ line } { }

std::size_t Token::line() const noexcept {
    return line_number_;
}

std::ostream& operator<<(std::ostream &os, const Token &token) {
    return token.print(os);
}

std::istream& operator>>(std::istream &is, TokenOwnerT &token) {
    std::size_t line;
    is >> line;

    if (!is) {
        return is;
    }

    std::string token_id;
    is >> token_id;

    if (!is) {
        return is;
    }

    if (token_id == "ip") {
        token = std::make_unique<token::IncrementPointer>(line);
    } else if (token_id == "dp") {
        token = std::make_unique<token::DecrementPointer>(line);
    } else if (token_id == "id") {
        token = std::make_unique<token::IncrementData>(line);
    } else if (token_id == "dd") {
        token = std::make_unique<token::DecrementData>(line);
    } else if (token_id == "oc") {
        token = std::make_unique<token::OutputCell>(line);
    } else if (token_id == "ic") {
        token = std::make_unique<token::InputCell>(line);
    } else if (token_id == "lb") {
        token = std::make_unique<token::LoopBegin>(line);
    } else if (token_id == "le") {
        token = std::make_unique<token::LoopEnd>(line);
    } else if (token_id == "co") {
        std::string comment;

        // eat the whitespace
        is.ignore(1);

        std::getline(is, comment);

        token = std::make_unique<token::Comment>(line, std::move(comment));
    }

    return is;
}

namespace token {

IncrementPointer::IncrementPointer(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& IncrementPointer::print(std::ostream &os) const {
    return os << Token::line() << " ip";
}

DecrementPointer::DecrementPointer(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& DecrementPointer::print(std::ostream &os) const {
    return os << Token::line() << " dp";
}

IncrementData::IncrementData(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& IncrementData::print(std::ostream &os) const {
    return os << Token::line() << " id";
}

DecrementData::DecrementData(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& DecrementData::print(std::ostream &os) const {
    return os << Token::line() << " dd";
}

OutputCell::OutputCell(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& OutputCell::print(std::ostream &os) const {
    return os << Token::line() << " oc";
}

InputCell::InputCell(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& InputCell::print(std::ostream &os) const {
    return os << Token::line() << " ic";
}

LoopBegin::LoopBegin(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& LoopBegin::print(std::ostream &os) const {
    return os << Token::line() << " lb";
}

LoopEnd::LoopEnd(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& LoopEnd::print(std::ostream &os) const {
    return os << Token::line() << " le";
}

Comment::Comment(const std::size_t line, const std::string_view comment)
: Token{ line }, comment_{ comment } { }

Comment::Comment(const std::size_t line, std::string &&comment) noexcept
: Token{ line }, comment_{ std::move(comment) } { }

std::ostream& Comment::print(std::ostream &os) const {
    return os << Token::line() << " co " << comment();
}

std::string_view Comment::comment() const noexcept {
    return comment_;
}

} // namespace token
} // namespace lexer
} // namespace bf
} // namespace gregjm
