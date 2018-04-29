#include "lexer.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

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

int main(const int argc, const char *argv[]) {
    if (argc != 3) {
        std::cerr << "usage: lexer INPUT OUTPUT" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const char *const input_filename = argv[1];
    const char *const output_filename = argv[2];

    auto [ifs, ofs] = open_files(input_filename, output_filename);

    gregjm::bf::Lexer lexer;
    auto tokens = lexer.tokenize(ifs);

    for (const auto &token_ptr : tokens) {
        ofs << *token_ptr << '\n';
    }
}
