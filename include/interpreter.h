#ifndef GREGJM_BF_INTERPRETER_H
#define GREGJM_BF_INTERPRETER_H

#include "interpreter/data_unit.h"
#include "interpreter/instruction_unit.h"
#include "interpreter/io_unit.h"

#include "exceptions.h"
#include "types.hpp"

#include <cstdint>
#include <array>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <stack>
#include <unordered_map>
#include <vector>

#include <gsl/gsl>

namespace gregjm {
namespace bf {

class Interpreter {
public:
    Interpreter(std::istream &input_stream, std::istream &instruction_stream,
                std::ostream &output_stream) noexcept;

    void step();

private:
    interpreter::DataUnit data_;
    interpreter::InstructionUnit instructions_;
    interpreter::IoUnit io_;
};

} // namespace bf
} // namespce gregjm

#endif
