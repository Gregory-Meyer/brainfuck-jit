#ifndef GREGJM_BF_INTERPRETER_INSTRUCTION_UNIT_H
#define GREGJM_BF_INTERPRETER_INSTRUCTION_UNIT_H

#include "interpreter/bracket_matcher.h"
#include "exceptions.h"
#include "types.hpp"

#include <cstddef>
#include <iostream>
#include <optional>

#include <gsl/gsl>

namespace gregjm {
namespace bf {
namespace interpreter {

class InstructionUnit {
public:
    InstructionUnit(std::istream &is) noexcept;

    // returns std::nullopt if the pointer is past
    // the end of the instruction buffer
    std::optional<InstructionT> current_instruction() const noexcept;

    // throws NoInstructionAvailable if !*stream_ptr
    InstructionT push_instruction();

    std::size_t ptr() const noexcept;

    // somewhat dubious to return a mut ref to a member
    std::size_t& ptr_mut() noexcept;

    void jump_forward_if_zero(CellT cell);

    void jump_backward_if_nonzero(CellT cell);

private:
    std::istream& stream() const noexcept;

    std::vector<InstructionT> instructions_;
    std::size_t instruction_pointer_;
    BracketMatcher matcher_;
    gsl::not_null<std::istream*> stream_ptr_;
};

} // namespace interpreter
} // namespace bf
} // namespace gregjm

#endif
