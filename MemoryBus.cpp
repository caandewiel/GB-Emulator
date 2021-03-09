//
// Created by Christian aan de Wiel on 08/03/2021.
//

#include "MemoryBus.h"

void MemoryBus::loadRom(std::vector<uint8_t> &&data) {
    std::copy(std::begin(data), std::end(data), std::begin(this->memory));
}

uint8_t MemoryBus::loadMemory(uint16_t address) {
    return this->memory[address];
}

void MemoryBus::storeMemory(uint16_t address, uint8_t value) {
    this->memory[address] = value;
}
