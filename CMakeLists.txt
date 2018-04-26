cmake_minimum_required(VERSION 3.8)

project(brainfuck-jit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-march=native -Wall -Wextra -Wconversion -Wshadow -Wcast-qual -pedantic -pedantic-errors -isystem .")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -g3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")

include_directories(include)

set(INTERPRETER_SOURCES src/interpreter.cpp src/exceptions.cpp
                        src/interpreter/bracket_matcher.cpp
                        src/interpreter/data_unit.cpp
                        src/interpreter/instruction_unit.cpp
                        src/interpreter/io_unit.cpp)

set(LEXER_SOURCES src/lexer.cpp)

add_executable(interpreter src/interpreter_main.cpp ${INTERPRETER_SOURCES})

add_executable(lexer src/lexer_main.cpp ${LEXER_SOURCES})
