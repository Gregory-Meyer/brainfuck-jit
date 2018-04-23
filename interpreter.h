#ifndef GREGJM_BF_INTERPRETER_H
#define GREGJM_BF_INTERPRETER_H

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

class BracketMatcher {
public:
    void push_left(std::size_t left);

    void push_right(std::size_t right);

    std::optional<std::size_t> match_left(std::size_t bracket);

    std::optional<std::size_t> match_right(std::size_t bracket);

private:
    bool is_left_bracket(std::size_t bracket) const noexcept;

    bool is_right_bracket(std::size_t bracket) const noexcept;

    enum class BracketType {
        Left,
        Right,
        Unknown
    };

    struct BracketPair {
        BracketType type = BracketType::Unknown;
        std::size_t match = std::numeric_limits<std::size_t>::max();
    };

    std::vector<BracketPair> bracket_map_;
    std::stack<std::size_t, std::vector<std::size_t>> unmatched_;
};

class Interpreter {
public:
    Interpreter(std::istream &input_stream, std::istream &instruction_stream,
                std::ostream &output_stream) noexcept;

    void step();

private:
    std::istream& input_stream() const noexcept;

    std::istream& instruction_stream() const noexcept;

    std::ostream& output_stream() const noexcept;

    InstructionT push_instruction();

    void bounds_check() const;

    CellT deref() const;

    CellT& deref_mut();

    void output();

    void input();

    void jump_forward();

    void jump_backward();

    void check_output_stream() const;

    void check_input_stream() const;

    std::unique_ptr<CellT[]> data_;
    gsl::not_null<CellT*> data_ptr_;
    std::vector<InstructionT> instructions_;
    std::size_t instruction_index_;
    BracketMatcher matcher_;
    gsl::not_null<std::istream*> input_stream_ptr_;
    gsl::not_null<std::istream*> instruction_stream_ptr_;
    gsl::not_null<std::ostream*> output_stream_ptr_;
};

} // namespace bf
} // namespce gregjm

#endif
