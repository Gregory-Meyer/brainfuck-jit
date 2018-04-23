#include "exceptions.h"
#include "interpreter.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

int main(const int argc, const char *const argv[]) {
    const std::vector<std::string_view> args{ argv, argv + argc };

    if (args.size() != 2) {
        std::cerr << "usage: interpreter FILE" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const std::string filename(args[1]);
    std::ifstream ifs{ filename };

    if (!ifs.is_open()) {
        std::cerr << "error: unable to open '" << filename << "'" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    gregjm::bf::Interpreter interpreter{ std::cin, ifs, std::cout };

    while (true) {
        try {
            interpreter.step();
        } catch (const gregjm::bf::NoInstructionAvailable &e) {
            break;
        } catch (const gregjm::bf::NoMatchingBracket &e) {
            static constexpr const char *const message =
                "error: no matching bracket";

            std::cerr << message << std::endl;
            std::exit(EXIT_FAILURE);
        } catch (const gregjm::bf::OutOfBounds &e) {
            static constexpr const char *const message =
                "error: attempted to dereference out of bounds";

            std::cerr << message << std::endl;
            std::exit(EXIT_FAILURE);
        } catch (const gregjm::bf::InputError &e) {
            static constexpr const char *const message =
                "error: could not read from input";

            std::cerr << message << std::endl;
            std::exit(EXIT_FAILURE);
        } catch (const gregjm::bf::OutputError &e) {
            static constexpr const char *const message =
                "error: could not write to output";

            std::cerr << message << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}
