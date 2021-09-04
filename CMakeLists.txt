cmake_minimum_required(VERSION 3.20)
project(bisim)

set(CMAKE_CXX_STANDARD 14)

add_executable(bisim main.cpp LogicBoard.cpp LogicBoard.h Primitive/Gates.cpp Primitive/Gates.h Primitive/IO.cpp Primitive/IO.h Primitive/CustomGates.h  SDDLParser.cpp SDDLParser.h Greetor.h)
