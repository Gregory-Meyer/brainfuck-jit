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

namespace detail {

static constexpr bool is_command(const char maybe_command) noexcept {
    switch (maybe_command) {
    case '>': case '<': case '+': case '-':
    case '.': case ',': case '[': case ']': {
        return true;
    } default: {
        return false;
    }
    }

}

} // namespace detail

std::vector<std::unique_ptr<Token>>
TokenFactory::make_tokens(const char maybe_command) {
    std::vector<std::unique_ptr<Token>> tokens;

    if (!comment_buffer_.empty()
        && (detail::is_command(maybe_command) || maybe_command == '\n')) {
        auto comment_owner =
            std::make_unique<token::Comment>(line_number_,
                                             std::move(comment_buffer_));
        tokens.push_back(std::move(comment_owner));
    }

    switch (maybe_command) {
    case '>': {
        auto token_owner =
            std::make_unique<token::IncrementPointer>(line_number_);
        tokens.push_back(std::move(token_owner));

        break;
    } case '<': {
        auto token_owner =
            std::make_unique<token::DecrementPointer>(line_number_);
        tokens.push_back(std::move(token_owner));

        break;
    } case '+': {
        auto token_owner =
            std::make_unique<token::IncrementData>(line_number_);
        tokens.push_back(std::move(token_owner));
        
        break;
    } case '-': {
        auto token_owner =
            std::make_unique<token::DecrementData>(line_number_);
        tokens.push_back(std::move(token_owner));
        
        break;
    } case '.': {
        auto token_owner =
            std::make_unique<token::OutputCell>(line_number_);
        tokens.push_back(std::move(token_owner));
        
        break;
    } case ',': {
        auto token_owner =
            std::make_unique<token::InputCell>(line_number_);
        tokens.push_back(std::move(token_owner));
        
        break;
    } case '[': {
        auto token_owner =
            std::make_unique<token::LoopBegin>(line_number_);
        tokens.push_back(std::move(token_owner));
        
        break;
    } case ']': {
        auto token_owner =
            std::make_unique<token::LoopEnd>(line_number_);
        tokens.push_back(std::move(token_owner));
        
        break;
    } case '\n': {
        ++line_number_;
        
        break;
    } default: {
        comment_buffer_.push_back(maybe_command);
    }
    }

    return tokens;
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
    return os << Token::line() << " co '" << comment() << '\'';
}

std::string_view Comment::comment() const noexcept {
    return comment_;
}

} // namespace token
} // namespace lexer
} // namespace bf
} // namespace gregjm
