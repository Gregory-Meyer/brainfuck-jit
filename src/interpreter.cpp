#include "interpreter.h"

namespace gregjm {
namespace bf {

static constexpr bool is_instruction(const char maybe_instruction) noexcept {
    switch (maybe_instruction) {
    case '>': case '<': case '+': case '-':
    case '.': case ',': case '[': case ']': {
        return true;
    }
    default: {
        return false;
    }
    }
}

Interpreter::Interpreter(std::istream &input_stream,
                         std::istream &instruction_stream,
                         std::ostream &output_stream)
noexcept : instructions_{ instruction_stream },
           io_{ input_stream, output_stream } { }

void Interpreter::step() {
    const InstructionT instruction = [this] {
        auto maybe_instruction = instructions_.current_instruction();

        while (!maybe_instruction.has_value()) {
            instructions_.push_instruction();
            maybe_instruction = instructions_.current_instruction();
        }

        return maybe_instruction.value();
    }();

    if (!is_instruction(instruction)) {
        throw InvalidInstruction{ instruction, "Interpreter::step" };
    }

    switch (instruction) {
    case '>': {
        data_.increment();
        break;
    };
    case '<': {
        data_.decrement();
        break;
    }
    case '+': {
        ++data_.deref_mut();
        break;
    }
    case '-': {
        --data_.deref_mut();
        break;
    }
    case '.': {
        io_.send_output(data_.deref());
        break;
    }
    case ',': {
        try {
            data_.deref_mut() = io_.get_input();
        } catch (const InputError &e) {
            if (e.type() != StreamError::Eof) {
                throw;
            }
        }

        break;
    }
    case '[': {
        instructions_.jump_forward_if_zero(data_.deref());
        break;
    }
    case ']': {
        instructions_.jump_backward_if_nonzero(data_.deref());
        break;
    }
    default: {
        __builtin_unreachable();
    }
    }

    ++instructions_.ptr_mut();
}

} // namespace bf
} // namespace gregjm
