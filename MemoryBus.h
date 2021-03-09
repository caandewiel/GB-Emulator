//
// Created by Christian aan de Wiel on 08/03/2021.
//

#ifndef GB_EMULATOR_MEMORYBUS_H
#define GB_EMULATOR_MEMORYBUS_H

#include <array>
#include <string>
#include <algorithm>
#include <vector>

class MemoryBus {
public:
    void loadRom(std::vector<uint8_t> &&data);
    uint8_t loadMemory(uint16_t address);
    void storeMemory(uint16_t address, uint8_t value);

private:
    std::array<uint8_t, 0xFFFF> memory;
};


#endif //GB_EMULATOR_MEMORYBUS_H
