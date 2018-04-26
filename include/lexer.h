#ifndef GREGJM_BF_LEXER_H
#define GREGJM_BF_LEXER_H

#include <iostream>
#include <vector>

namespace gregjm {
namespace bf {
namespace lexer {

enum class Token {
    IncrementPointer,
    DecrementPointer,
    IncrementData,
    DecrementData,
    OutputCell,
    InputCell,
    LoopBegin,
    LoopEnd
};

} // namespace lexer

class Lexer {
public:
    std::vector<lexer::Token> tokenize(std::istream &is);

private:
    std::vector<lexer::Token> tokens_;
};

} // namespace bf
} // namespace gregjm

#endif
