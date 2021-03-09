//
// Created by Christian aan de Wiel on 03/03/2021.
//
#include "GameBoy.h"

int main() {
    GameBoy gameBoy;
    gameBoy.loadRom("/Users/christian/GB-Emulator/cpu_instrs.gb");
    gameBoy.run();
}

