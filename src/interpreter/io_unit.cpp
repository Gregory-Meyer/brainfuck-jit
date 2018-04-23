#include "interpreter/io_unit.h"

#include <iomanip>

namespace gregjm {
namespace bf {
namespace interpreter {

IoUnit::IoUnit(std::istream &input_stream, std::ostream &output_stream)
noexcept : input_stream_ptr_{ &input_stream },
           output_stream_ptr_{ &output_stream } { }

CellT IoUnit::get_input() {
    CellT input;
    input_stream() >> std::noskipws >> input;

    check_input_stream();

    return input;
}

void IoUnit::send_output(const CellT to_output) {
    const auto as_char = static_cast<char>(to_output);

    output_stream() << as_char;

    check_output_stream();
}

void IoUnit::check_input_stream() const {
    if (!input_stream()) {
        if (input_stream().bad()) {
            throw InputError{ StreamError::Bad,
                              "IoUnit::check_input_stream" };
        }

        throw InputError{ StreamError::Fail,
                          "IoUnit::check_input_stream" };
    } else if (input_stream().eof()) {
        throw InputError{ StreamError::Eof, "IoUnit::check_input_stream" };
    }
}

void IoUnit::check_output_stream() const {
    if (!output_stream()) {
        if (output_stream().bad()) {
            throw OutputError{ StreamError::Bad,
                               "IoUnit::check_output_stream" };
        }

        throw OutputError{ StreamError::Fail,
                           "IoUnit::check_output_stream" };
    } else if (output_stream().eof()) {
        throw OutputError{ StreamError::Eof,
                           "IoUnit::check_output_stream" };
    }
}

std::istream& IoUnit::input_stream() const noexcept {
    return *input_stream_ptr_;
}

std::ostream& IoUnit::output_stream() const noexcept {
    return *output_stream_ptr_;
}

} // namespace interpreter
} // namespace bf
} // namespace gregjm
