CXXFLAGS = -O3 -std=c++17 -march=native -Wall -Wextra -Wconversion -Wshadow -Wcast-qual -pedantic -pedantic-errors -isystem .
CXX = g++ 

all: interpreter

interpreter: exceptions.o interpreter.o interpreter_main.o
	${CXX} ${CXXFLAGS} exceptions.o interpreter.o interpreter_main.o -o interpreter

interpreter.o: interpreter.h interpreter.cpp exceptions.h types.hpp
	${CXX} ${CXXFLAGS} -c interpreter.cpp

exceptions.o: exceptions.h exceptions.cpp types.hpp
	${CXX} ${CXXFLAGS} -c exceptions.cpp

interpreter_main.o: interpreter_main.cpp interpreter.h exceptions.h
	${CXX} ${CXXFLAGS} -c interpreter_main.cpp

.PHONY: clean
clean:
	rm -f exceptions.o interpreter.o interpreter_main.o interpreter interpreter.exe
