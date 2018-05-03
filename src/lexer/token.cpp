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
        token = std::make_unique<IncrementPointerToken>(line);
    } else if (token_id == "dp") {
        token = std::make_unique<DecrementPointerToken>(line);
    } else if (token_id == "id") {
        token = std::make_unique<IncrementDataToken>(line);
    } else if (token_id == "dd") {
        token = std::make_unique<DecrementDataToken>(line);
    } else if (token_id == "oc") {
        token = std::make_unique<OutputCellToken>(line);
    } else if (token_id == "ic") {
        token = std::make_unique<InputCellToken>(line);
    } else if (token_id == "lb") {
        token = std::make_unique<LoopBeginToken>(line);
    } else if (token_id == "le") {
        token = std::make_unique<LoopEndToken>(line);
    } else if (token_id == "co") {
        std::string comment;

        // eat the whitespace
        is.ignore(1);

        std::getline(is, comment);

        token = std::make_unique<CommentToken>(line, std::move(comment));
    }

    return is;
}

IncrementPointerToken::IncrementPointerToken(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& IncrementPointerToken::print(std::ostream &os) const {
    return os << Token::line() << " ip";
}

DecrementPointerToken::DecrementPointerToken(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& DecrementPointerToken::print(std::ostream &os) const {
    return os << Token::line() << " dp";
}

IncrementDataToken::IncrementDataToken(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& IncrementDataToken::print(std::ostream &os) const {
    return os << Token::line() << " id";
}

DecrementDataToken::DecrementDataToken(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& DecrementDataToken::print(std::ostream &os) const {
    return os << Token::line() << " dd";
}

OutputCellToken::OutputCellToken(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& OutputCellToken::print(std::ostream &os) const {
    return os << Token::line() << " oc";
}

InputCellToken::InputCellToken(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& InputCellToken::print(std::ostream &os) const {
    return os << Token::line() << " ic";
}

LoopBeginToken::LoopBeginToken(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& LoopBeginToken::print(std::ostream &os) const {
    return os << Token::line() << " lb";
}

LoopEndToken::LoopEndToken(const std::size_t line) noexcept
: Token{ line } { }

std::ostream& LoopEndToken::print(std::ostream &os) const {
    return os << Token::line() << " le";
}

CommentToken::CommentToken(const std::size_t line,
                           const std::string_view comment)
: Token{ line }, comment_{ comment } { }

CommentToken::CommentToken(const std::size_t line, std::string &&comment) noexcept
: Token{ line }, comment_{ std::move(comment) } { }

std::ostream& CommentToken::print(std::ostream &os) const {
    return os << Token::line() << " co " << comment();
}

std::string_view CommentToken::comment() const noexcept {
    return comment_;
}

} // namespace lexer
} // namespace bf
} // namespace gregjm
