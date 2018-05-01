#include "container_types.hpp"
#include "parser.h"
#include "lexer/token.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

#include <range/v3/all.hpp>

static std::pair<std::ifstream, std::ofstream>
open_files(const char *const input, const char *const output) {
    std::ifstream ifs{ input };

    if (!ifs.is_open()) {
        std::cerr << "error: unable to open '" << input << "'" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::ofstream ofs{ output };

    if (!ofs.is_open()) {
        std::cerr << "error: unable to open '" << input << "'" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return { std::move(ifs), std::move(ofs) };
}

static std::reference_wrapper<const gregjm::bf::lexer::Token>
owner_as_ref(const gregjm::bf::lexer::TokenOwnerT &owner) {
    return { *owner };
}

static gregjm::bf::TokenOwnerContainerT parse_tokens(std::istream &is) {
    gregjm::bf::TokenOwnerContainerT tokens;
    for (gregjm::bf::lexer::TokenOwnerT token; is >> token;) {
        tokens.push_back(std::move(token));
    }

    return tokens;
}

int main(const int argc, const char *argv[]) {
    if (argc != 3) {
        std::cerr << "usage: parser_main INPUT OUTPUT" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const char *const input_filename = argv[1];
    const char *const output_filename = argv[2];

    auto [ifs, ofs] = open_files(input_filename, output_filename);

    const gregjm::bf::TokenOwnerContainerT token_owners = parse_tokens(ifs);

    gregjm::bf::Parser parser{ token_owners
                               | ranges::view::transform(&owner_as_ref) };

    gregjm::bf::parser::AbstractSyntaxTree ast = parser.build_tree();
}
