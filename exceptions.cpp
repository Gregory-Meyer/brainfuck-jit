#include "exceptions.h"

namespace gregjm {
namespace bf {

NoInstructionAvailable::NoInstructionAvailable(const std::string &what)
: std::runtime_error{ what } { }

NoInstructionAvailable::NoInstructionAvailable(const char *const what)
: std::runtime_error{ what } { }

InvalidInstruction::InvalidInstruction(const InstructionT instruction,
                                       const std::string &what)
: std::logic_error{ what }, instruction_{ instruction } { }

InvalidInstruction::InvalidInstruction(const InstructionT instruction,
                                       const char *const what)
: std::logic_error{ what }, instruction_{ instruction } { }

InstructionT InvalidInstruction::instruction() const noexcept {
    return instruction_;
}

OutOfBounds::OutOfBounds(const std::string &what)
: std::runtime_error{ what } { }

OutOfBounds::OutOfBounds(const char *const what)
: std::runtime_error{ what } { }

InputError::InputError(const StreamError error, const std::string &what)
: std::runtime_error{ what }, error_{ error } { }

InputError::InputError(const StreamError error, const char *const what)
: std::runtime_error{ what }, error_{ error } { }

StreamError InputError::type() const noexcept {
    return error_;
}

OutputError::OutputError(const StreamError error, const std::string &what)
: std::runtime_error{ what }, error_{ error } { }

OutputError::OutputError(const StreamError error, const char *const what)
: std::runtime_error{ what }, error_{ error } { }

StreamError OutputError::type() const noexcept {
    return error_;
}

NoMatchingBracket::NoMatchingBracket(const std::string &what)
: std::logic_error{ what } { }

NoMatchingBracket::NoMatchingBracket(const char *const what)
: std::logic_error{ what } { }

} // namespace bf
} // namespace gregjm
