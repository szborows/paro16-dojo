#define CATCH_CONFIG_MAIN
#include <string>
#include <catch.hpp>

#include "Brainfuck.hpp"

TEST_CASE( "Brainfuck interpreter test cases", "[interp]" ) {

    Brainfuck interpreter;

    SECTION( "empty code evaluates to empty result" ) {
        Code code{""};
        Input input{""};
        REQUIRE( interpreter.interpret(code, input) == "" );
    }

    SECTION( "outputting memory without any prior operations yields zeroes" ) {
        Code code{".........."};
        Input input{""};
        REQUIRE( interpreter.interpret(code, input) == std::string("\0\0\0\0\0\0\0\0\0\0", 10) );
    }

    SECTION( "streaming input to output works correctly" ) {
        Code code{",.,..,...,...."};
        Input input{"abcd"};
        REQUIRE( interpreter.interpret(code, input) == "abbcccdddd" );
    }

    SECTION( "incrementing/decrementing at memory pointer results in correct numbers" ) {
        Code code{",.+.++.+++.---.--.-."};
        Input input{"\1"};
        REQUIRE( interpreter.interpret(code, input) == "\1\2\4\7\4\2\1" );
    }

    SECTION( "memory can be traversed" ) {
        Code code{",>,>,>,<<<.>.>.>.<.<.<."};
        Input input{"abcd"};
        REQUIRE( interpreter.interpret(code, input) == "abcdcba" );
    }

    SECTION( "simple loops' steps are stepped through" ) {
        Code code{",[.]"};
        Input input{"\5"};
        REQUIRE( interpreter.interpret(code, input) == std::string("\4\3\2\1\0", 5) );
    }

    SECTION( "nested loops' are evaluated in order" ) {
        Code code{",[.>+[+.-]<]"};
        Input input{"\5"};
        REQUIRE( interpreter.interpret(code, input) == std::string("\4\1\3\1\2\1\1\1\0\1", 10) );
    }

    SECTION( "nested loops' are evaluated in order - doubled" ) {
        Code code{",[.>+[+.-]<],[.>+[+.-]<]"};
        Input input{"\5\5"};
        REQUIRE( interpreter.interpret(code, input) == std::string("\4\1\3\1\2\1\1\1\0\1"
            "\4\1\3\1\2\1\1\1\0\1", 20) );
    }

    SECTION( "comments are ignored" ) {
        Code code{"qwertyuiopasdfghjklzxcvbnm,."};
        Input input{"a"};
        REQUIRE( interpreter.interpret(code, input) == "a" );
    }

    SECTION( "self interpreter" ) {
        Code code{
            ">>>+[[-]>>[-]++>+>+++++++[<++++>>++<-]++>>+>+>+++++[>++>++++++<<-]+>>>,<++[[>["
            "->>]<[>>]<<-]<[<]<+>>[>]>[<+>-[[<+>-]>]<[[[-]<]++<-[<+++++++++>[<->-]>>]>>]]<<"
            "]<]<[[<]>[[>]>>[>>]+[<<]<[<]<+>>-]>[>]+[->>]<<<<[[<<]<[<]+<<[+>+<<-[>-->+<<-[>"
            "+<[>>+<<-]]]>[<+>-]<]++>>-->[>]>>[>>]]<<[>>+<[[<]<]>[[<<]<[<]+[-<+>>-[<<+>++>-"
            "[<->[<<+>>-]]]<[>+<-]>]>[>]>]>[>>]>>]<<[>>+>>+>>]<<[->>>>>>>>]<<[>.>>>>>>>]<<["
            ">->>>>>]<<[>,>>>]<<[>+>]<<[+<<]<]"
        };
        Input input{",.!a"};
        REQUIRE( interpreter.interpret(code, input) == "a" );
    }
}

