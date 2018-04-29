#include "lexer.h"

#include <array>
#include <string>
#include <utility>

namespace gregjm {
namespace bf {

std::vector<std::unique_ptr<lexer::Token>> Lexer::tokenize(std::istream &is) {
    const std::string buffer = [&is] {
        const std::istreambuf_iterator<char> first{ is };
        const std::istreambuf_iterator<char> last;

        const std::string buf(first, last);

        return buf;
    }();

    tokens_.reserve(buffer.size());
    lexer::TokenFactory factory;

    for (const char maybe_command : buffer) {
        auto tokens = factory.make_tokens(maybe_command);
        auto begin = std::make_move_iterator(tokens.begin());
        auto end = std::make_move_iterator(tokens.end());

        tokens_.insert(tokens_.cend(), begin, end);
    }

    return std::move(tokens_);
}

} // namespace bf
} // namespace gregjm
