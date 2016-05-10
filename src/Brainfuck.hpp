#pragma once
#include <string>

using Code = std::string;
using Input = std::string;

struct Brainfuck final {
    Brainfuck() = default;
    std::string interpret(Code const& code, Input const& input) const;

    Brainfuck(Brainfuck const&) = delete;
    Brainfuck& operator=(Brainfuck const&) = delete;
};
