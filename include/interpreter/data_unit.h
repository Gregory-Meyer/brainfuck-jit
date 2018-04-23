#ifndef GREGJM_BF_INTERPRETER_DATA_UNIT_H
#define GREGJM_BF_INTERPRETER_DATA_UNIT_H

#include "types.hpp"

#include <cstddef>
#include <vector>

namespace gregjm {
namespace bf {
namespace interpreter {

class DataUnit {
public:
    CellT deref() const;

    CellT& deref_mut();

    void increment() noexcept;

    void decrement() noexcept;

private:
    static std::size_t left_index(std::ptrdiff_t index) noexcept;

    mutable std::vector<CellT> right_memory_;
    mutable std::vector<CellT> left_memory_;
    std::ptrdiff_t pointer_ = 0;
};

} // namespace interpreter
} // namespace bf
} // namespace gregjm

#endif
