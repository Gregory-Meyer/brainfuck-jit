#ifndef GREGJM_BF_INTERPRETER_IO_UNIT_H
#define GREGJM_BF_INTERPRETER_IO_UNIT_H

#include "exceptions.h"
#include "types.hpp"

#include <iostream>

#include <gsl/gsl>

namespace gregjm {
namespace bf {
namespace interpreter {

class IoUnit {
public:
    IoUnit(std::istream &input_stream, std::ostream &output_stream) noexcept;

    CellT get_input();

    void send_output(CellT to_output);

private:
    void check_input_stream() const;

    void check_output_stream() const;

    std::istream& input_stream() const noexcept;

    std::ostream& output_stream() const noexcept;

    gsl::not_null<std::istream*> input_stream_ptr_;
    gsl::not_null<std::ostream*> output_stream_ptr_;
};

} // namespace interpreter
} // namespace bf
} // namespace gregjm

#endif
