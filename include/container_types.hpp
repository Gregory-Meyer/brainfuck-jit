#ifndef GREGJM_BF_CONTAINER_TYPES_HPP
#define GREGJM_BF_CONTAINER_TYPES_HPP

#include "lexer/token.h"

#include <functional>
#include <memory>
#include <vector>

#include <gsl/gsl>

namespace gregjm {
namespace bf {

using TokenOwnerContainerT = std::vector<lexer::TokenOwnerT>;
using TokenRefContainerT =
    std::vector<std::reference_wrapper<const lexer::Token>>;

}
}

#endif
