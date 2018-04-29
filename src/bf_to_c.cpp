#include <cstdlib>
#include <iostream>
#include <fstream>

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

static void prelude(std::ostream &os) {
    os << "#include <stdio.h>\n"
       << '\n'
       << "int main(void) {\n"
       << "    char data[30000] = { 0 };\n"
       << "    char *ptr = data;\n";
}

static void postlude(std::ostream &os) {
    os << "}\n";
}

static void print_tab_spaces(std::ostream &os,
                             const std::size_t num_tab_spaces) {
    for (std::size_t i = 0; i < num_tab_spaces; ++i) {
        os << ' ';
    }
}

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

static void port(std::istream &is, std::ostream &os) {
    std::size_t num_tab_spaces = 4;

    for (char maybe_command; is >> maybe_command;) {
        if (!is_command(maybe_command)) {
            continue;
        }

        if (maybe_command == ']') {
            num_tab_spaces -= 4;
        }

        print_tab_spaces(os, num_tab_spaces);

        switch (maybe_command) {
        case '>': {
            os << "++ptr;";

            break;
        } case '<': {
            os << "--ptr;";

            break;
        } case '+': {
            os << "++*ptr;";

            break;
        } case '-': {
            os << "--*ptr;";

            break;
        } case '.': {
            os << "putchar(*ptr);";

            break;
        } case ',': {
            os << "*ptr = (char) getchar();";

            break;
        } case '[': {
            os << "while (*ptr) {";

            num_tab_spaces += 4;

            break;
        } case ']': {
            os << "}";

            break;
        } default: {
            __builtin_unreachable();
        }
        }

        os << '\n';
    }
}

int main(const int argc, const char *const argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    if (argc != 3) {
        std::cerr << "usage: bf-to-c INPUT OUTPUT" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const char *const input_filename = argv[1];
    const char *const output_filename = argv[2];

    auto [ifs, ofs] = open_files(input_filename, output_filename);

    prelude(ofs);
    port(ifs, ofs);
    postlude(ofs);
}
