cmake_minimum_required(VERSION 3.14)

set (CMAKE_CXX_STANDARD 20)
project(GB_Emulator VERSION 1.0 LANGUAGES CXX)

add_executable(GB_Emulator main.cpp opcode.hpp Disassembler.h Disassembler.cpp MemoryBus.cpp MemoryBus.cpp CPU.h CPU.cpp GameBoy.h GameBoy.cpp)