#include "interpreter/data_unit.h"

namespace gregjm {
namespace bf {
namespace interpreter {

CellT DataUnit::deref() const {
    if (pointer_ >= 0) {
        const auto index = static_cast<std::size_t>(pointer_);

        if (index >= right_memory_.size()) {
            right_memory_.resize(index + 1, 0);
        }

        return right_memory_[index];
    }

    const std::size_t index = left_index(pointer_);

    if (index >= left_memory_.size()) {
        left_memory_.resize(index + 1, 0);
    }

    return left_memory_[index];
}

CellT& DataUnit::deref_mut() {
    if (pointer_ >= 0) {
        const auto index = static_cast<std::size_t>(pointer_);

        if (index >= right_memory_.size()) {
            right_memory_.resize(index + 1, 0);
        }

        return right_memory_[index];
    }

    const std::size_t index = left_index(pointer_);

    if (index >= left_memory_.size()) {
        left_memory_.resize(index + 1, 0);
    }

    return left_memory_[index];
}

void DataUnit::increment() noexcept {
    ++pointer_;
}

void DataUnit::decrement() noexcept {
    --pointer_;
}

std::size_t DataUnit::left_index(const std::ptrdiff_t index) noexcept {
    const auto as_usize = static_cast<std::size_t>(-index - 1);

    return as_usize;
}

} // namespace interpreter
} // namespace bf
} // namespace gregjm
