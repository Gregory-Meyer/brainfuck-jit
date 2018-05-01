#include "lexer/token_factory.h"

#include <utility>

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

namespace gregjm {
namespace bf {
namespace lexer {

TokenOwnerContainerT TokenFactory::make_tokens(const char maybe_command) {
    TokenOwnerContainerT tokens;

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

} // namespace lexer
} // namespace bf
} // namespace gregjm
