#include "interpreter/instruction_unit.h"

namespace gregjm {
namespace bf {
namespace interpreter {

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

InstructionUnit::InstructionUnit(std::istream &is) noexcept
: stream_ptr_{ &is } { }

std::optional<InstructionT> InstructionUnit::current_instruction()
const noexcept {
    if (instruction_pointer_ >= instructions_.size()) {
        return std::nullopt;
    }

    return std::make_optional(instructions_[instruction_pointer_]);
}

InstructionT InstructionUnit::push_instruction() {
    const InstructionT next_instruction = [this] {
        for (char buffer; stream() >> std::skipws >> buffer;) {
            if (is_instruction(buffer)) {
                return static_cast<InstructionT>(buffer);
            }
        }

        throw NoInstructionAvailable{
            "InstructionUnit::push_instruction"
        };
    }();

    if (static_cast<char>(next_instruction) == '[') {
        matcher_.push_left(instructions_.size());
    } else if (static_cast<char>(next_instruction) == ']') {
        matcher_.push_right(instructions_.size());
    }

    instructions_.push_back(next_instruction);
    return next_instruction;
}

std::size_t InstructionUnit::ptr() const noexcept {
    return instruction_pointer_;
}

std::size_t& InstructionUnit::ptr_mut() noexcept {
    return instruction_pointer_;
}

void InstructionUnit::jump_forward_if_zero(const CellT cell) {
    if (cell != 0) {
        return;
    }

    const std::size_t match = [this] {
        auto maybe_match = matcher_.match_left(ptr());

        while (!maybe_match.has_value()) {
            try {
                push_instruction();
            } catch (const NoInstructionAvailable &e) {
                throw NoMatchingBracket{ "InstructionUnit::jump_forward" };
            }

            maybe_match = matcher_.match_left(ptr());
        }

        return maybe_match.value();
    }();

    ptr_mut() = match;
}

void InstructionUnit::jump_backward_if_nonzero(const CellT cell) {
    if (cell == 0) {
        return;
    }

    const std::size_t match = [this] {
        auto maybe_match = matcher_.match_right(ptr());

        if (!maybe_match.has_value()) {
            throw NoMatchingBracket{ "InstructionUnit::jump_backward" };
        }

        return maybe_match.value();
    }();

    ptr_mut() = match;
}

std::istream& InstructionUnit::stream() const noexcept {
    return *stream_ptr_;
}

} // namespace interpreter
} // namespace bf
} // namespace gregjm
