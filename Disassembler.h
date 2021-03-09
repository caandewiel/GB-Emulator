//
// Created by Christian aan de Wiel on 03/03/2021.
//

#ifndef GB_EMULATOR_DISASSEMBLER_H
#define GB_EMULATOR_DISASSEMBLER_H

#include <iostream>
#include <array>

#include "MemoryBus.h"

class Disassembler {
public:
    static void execute(std::vector<uint8_t> &_rom);

private:
    static std::unique_ptr<MemoryBus> memoryBus;

    static uint16_t programCounter;
    static uint16_t stackPointer;
    static std::array<uint8_t, 8> singleRegister;

    static void decode(uint8_t operation);
    static uint8_t load(uint16_t index);
};


#endif //GB_EMULATOR_DISASSEMBLER_H
