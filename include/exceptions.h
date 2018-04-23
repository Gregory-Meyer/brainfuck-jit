#ifndef GREGJM_BF_EXCEPTIONS_H
#define GREGJM_BF_EXCEPTIONS_H

#include "types.hpp"

#include <cstdint>
#include <stdexcept>
#include <string>

namespace gregjm {
namespace bf {

class NoInstructionAvailable : public std::runtime_error {
public:
    explicit NoInstructionAvailable(const std::string &what);

    explicit NoInstructionAvailable(const char *what);

    virtual ~NoInstructionAvailable() = default;
};

class InvalidInstruction : public std::logic_error {
public:
    explicit InvalidInstruction(InstructionT instruction,
                                const std::string &what);

    explicit InvalidInstruction(InstructionT instruction,
                                const char *what);

    virtual ~InvalidInstruction() = default;

    InstructionT instruction() const noexcept;

private:
    InstructionT instruction_;
};

class OutOfBounds : public std::runtime_error {
public:
    explicit OutOfBounds(const std::string &what);

    explicit OutOfBounds(const char *what);

    virtual ~OutOfBounds() = default;
};

enum class StreamError {
    Eof,
    Fail,
    Bad
};

class InputError : public std::runtime_error {
public:
    explicit InputError(StreamError error, const std::string &what);

    explicit InputError(StreamError error, const char *what);

    virtual ~InputError() = default;

    StreamError type() const noexcept;

public:
    StreamError error_;
};

class OutputError : public std::runtime_error {
public:
    explicit OutputError(StreamError error, const std::string &what);

    explicit OutputError(StreamError error, const char *what);

    virtual ~OutputError() = default;

    StreamError type() const noexcept;

public:
    StreamError error_;
};

class NoMatchingBracket : public std::logic_error {
public:
    explicit NoMatchingBracket(const std::string &what);

    explicit NoMatchingBracket(const char *what);

    virtual ~NoMatchingBracket() = default;
};

} // namespace bf
} // namespace gregjm

#endif
