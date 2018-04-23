#include "interpreter.h"

#include <cassert>

namespace gregjm {
namespace bf {

static constexpr std::size_t DATA_SIZE = 30000;

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

void BracketMatcher::push_left(const std::size_t left) {
    unmatched_.push(left);
}

void BracketMatcher::push_right(const std::size_t right) {
    const std::size_t left = unmatched_.top();
    unmatched_.pop();

    if (bracket_map_.size() <= right) {
        bracket_map_.resize(right + 1);
    }

    bracket_map_[left].type = BracketType::Left;
    bracket_map_[right].type = BracketType::Right;
    bracket_map_[left].match = right;
    bracket_map_[right].match = left;
}

std::optional<std::size_t>
BracketMatcher::match_left(const std::size_t bracket) {
    if (bracket >= bracket_map_.size() || !is_left_bracket(bracket)) {
        return std::nullopt;
    }

    return std::make_optional(bracket_map_[bracket].match);
}

std::optional<std::size_t>
BracketMatcher::match_right(const std::size_t bracket) {
    if (bracket >= bracket_map_.size() || !is_right_bracket(bracket)) {
        return std::nullopt;
    }

    return std::make_optional(bracket_map_[bracket].match);
}

bool BracketMatcher::is_left_bracket(const std::size_t bracket)
const noexcept {
    return bracket_map_[bracket].type == BracketType::Left;
}

bool BracketMatcher::is_right_bracket(const std::size_t bracket)
const noexcept {
    return bracket_map_[bracket].type == BracketType::Right;
}

Interpreter::Interpreter(std::istream &input_stream,
                         std::istream &instruction_stream,
                         std::ostream &output_stream)
noexcept : data_{ std::make_unique<CellT[]>(DATA_SIZE) },
           data_ptr_{ data_.get() }, instruction_index_{ 0 },
           input_stream_ptr_{ &input_stream },
           instruction_stream_ptr_{ &instruction_stream },
           output_stream_ptr_{ &output_stream } { }

void Interpreter::step() {
    while (instruction_index_ >= instructions_.size()) {
        push_instruction();
    }

    const InstructionT instruction = instructions_[instruction_index_];

    if (!is_instruction(instruction)) {
        throw InvalidInstruction{ instruction, "Interpreter::step" };
    }

    switch (instruction) {
    case '>': {
        data_ptr_ = data_ptr_.get() + 1;
        break;
    };
    case '<': {
        data_ptr_ = data_ptr_.get() - 1;
        break;
    }
    case '+': {
        ++deref_mut();
        break;
    }
    case '-': {
        --deref_mut();
        break;
    }
    case '.': {
        output();
        break;
    }
    case ',': {
        input();
        break;
    }
    case '[': {
        jump_forward();
        break;
    }
    case ']': {
        jump_backward();
        break;
    }
    default: {
        __builtin_unreachable();
    }
    }

    ++instruction_index_;
}

std::istream& Interpreter::input_stream() const noexcept {
    return *input_stream_ptr_;
}

std::istream& Interpreter::instruction_stream() const noexcept {
    return *instruction_stream_ptr_;
}

std::ostream& Interpreter::output_stream() const noexcept {
    return *output_stream_ptr_;
}

InstructionT Interpreter::push_instruction() {
    if (!instruction_stream()) {
        throw NoInstructionAvailable{ "Interpreter::push_instruction" };
    }

    const InstructionT instruction = [this] {
        char maybe_instruction = static_cast<char>(instruction_stream().get());

        while (instruction_stream() && !is_instruction(maybe_instruction)) {
            maybe_instruction = static_cast<char>(instruction_stream().get());
        }

        if (!instruction_stream()) {
            throw NoInstructionAvailable{ "Interpreter::push_instruction" };
        }

        return static_cast<InstructionT>(maybe_instruction);
    }();

    if (static_cast<char>(instruction) == '[') {
        matcher_.push_left(instructions_.size());
    } else if (static_cast<char>(instruction) == ']') {
        matcher_.push_right(instructions_.size());
    }

    instructions_.push_back(instruction);

    return instruction;
}

void Interpreter::bounds_check() const {
    if (data_ptr_ < data_.get() || data_ptr_ >= data_.get() + DATA_SIZE) {
        throw OutOfBounds{ "Interpreter::bounds_check" };
    }
}

CellT Interpreter::deref() const {
    bounds_check();

    return *data_ptr_;
}

CellT& Interpreter::deref_mut() {
    bounds_check();

    return *data_ptr_;
}

void Interpreter::output() {
    check_output_stream();

    const char to_output = static_cast<char>(deref());

    output_stream().put(to_output);

    check_output_stream();
}

void Interpreter::input() {
    check_input_stream();

    const auto input = static_cast<CellT>(input_stream().get());

    check_input_stream();

    deref_mut() = input;
}

void Interpreter::jump_forward() {
    if (deref() != 0) {
        return;
    }

    const std::size_t next_instruction_index = [this] {
        auto maybe_instruction = matcher_.match_left(instruction_index_);

        while (!maybe_instruction.has_value()) {
            try {
                push_instruction();
            } catch (const NoInstructionAvailable &e) {
                throw NoMatchingBracket{ "Interpreter::jump_forward" };
            }

            maybe_instruction = matcher_.match_left(instruction_index_);
        }

        return maybe_instruction.value();
    }();

    instruction_index_ = next_instruction_index;
}

void Interpreter::jump_backward() {
    if (deref() == 0) {
        return;
    }

    const std::size_t next_instruction_index = [this] {
        const auto maybe_instruction =
            matcher_.match_right(instruction_index_);

        if (!maybe_instruction.has_value()) {
            throw NoMatchingBracket{ "Interpreter::jump_backward" };
        }

        return maybe_instruction.value();
    }();

    instruction_index_ = next_instruction_index;
}

void Interpreter::check_output_stream() const {
    if (!output_stream()) {
        if (output_stream().bad()) {
            throw OutputError{ StreamError::Bad,
                               "Interpreter::check_output_stream" };
        } else if (output_stream().fail()) {
            throw OutputError{ StreamError::Fail,
                               "Interpreter::check_output_stream" };
        } else if (output_stream().eof()) {
            throw OutputError{ StreamError::Eof,
                               "Interpreter::check_output_stream" };
        }

        throw OutputError{ StreamError::Other,
                           "Interpreter::check_output_stream" };
    }
}

void Interpreter::check_input_stream() const {
    if (!input_stream()) {
        if (input_stream().bad()) {
            throw InputError{ StreamError::Bad,
                              "Interpreter::check_input_stream" };
        } else if (input_stream().fail()) {
            throw InputError{ StreamError::Fail,
                              "Interpreter::check_input_stream" };
        } else if (input_stream().eof()) {
            throw InputError{ StreamError::Eof,
                              "Interpreter::check_input_stream" };
        }

        throw InputError{ StreamError::Other,
                          "Interpreter::check_input_stream" };
    }
}

} // namespace bf
} // namespace gregjm
