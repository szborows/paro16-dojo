#include "Brainfuck.hpp"
#include "Memory.hpp"

std::string Brainfuck::interpret(Code const& code, Input const& input) const {
    Memory memory;
    std::string result;
    auto it = code.begin();
    auto inputIt = input.begin();
    while (it != code.end()) {
        switch (*it) {
            case '.': result += memory.get(); ++it;            break;
            case ',': memory.set(*inputIt);   ++it; ++inputIt; break;
            case '+': memory.increment();     ++it;            break;
            case '-': memory.decrement();     ++it;            break;
            case '<': memory.moveLeft();      ++it;            break;
            case '>': memory.moveRight();     ++it;            break;
            case '[':
                if (0 == memory.get()) {
                    for (auto brackets = 0;; ++it) {
                        if (*it == '[') { ++brackets;  }
                        if (*it == ']') { --brackets;  }
                        if (!brackets)  { ++it; break; }
                    }
                }
                else { memory.decrement(); ++it; }
                break;
            case ']':
                for (auto brackets = 0; ; --it) {
                    if (*it == ']') { ++brackets; }
                    if (*it == '[') { --brackets; }
                    if (!brackets)  { break; }
                }
                break;
            default: ++it; break;
        }
    }

    return result;
}
