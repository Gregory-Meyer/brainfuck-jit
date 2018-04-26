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

    return std::make_pair(std::move(ifs), std::move(ofs));
}

constexpr static std::string_view
token_as_string(const gregjm::bf::lexer::Token token) noexcept {
    switch (token) {
        case gregjm::bf::lexer::Token::IncrementPointer: return "ip";
        case gregjm::bf::lexer::Token::DecrementPointer: return "dp";
        case gregjm::bf::lexer::Token::IncrementData: return "id";
        case gregjm::bf::lexer::Token::DecrementData: return "dd";
        case gregjm::bf::lexer::Token::OutputCell: return "oc";
        case gregjm::bf::lexer::Token::InputCell: return "ic";
        case gregjm::bf::lexer::Token::LoopBegin: return "lb";
        case gregjm::bf::lexer::Token::LoopEnd: return "le";
    }

    __builtin_unreachable();
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
    std::vector<gregjm::bf::lexer::Token> tokens = lexer.tokenize(ifs);

    for (const auto token : tokens) {
        ofs << token_as_string(token) << '\n';
    }
}
