//
// Created by Christian aan de Wiel on 08/03/2021.
//

#ifndef GB_EMULATOR_GAMEBOY_H
#define GB_EMULATOR_GAMEBOY_H

#include <iostream>
#include <fstream>
#include <string>

#include "MemoryBus.h"
#include "CPU.h"

class GameBoy {
public:
    GameBoy();
    void loadRom(const std::string &filename);
    void run();

private:
    std::unique_ptr<CPU> cpu;
    std::shared_ptr<MemoryBus> memoryBus;
};


#endif //GB_EMULATOR_GAMEBOY_H
