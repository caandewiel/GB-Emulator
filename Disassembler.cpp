//
// Created by Christian aan de Wiel on 03/03/2021.
//

#include "Disassembler.h"

uint16_t Disassembler::programCounter = 0x100;
uint16_t Disassembler::stackPointer = 0x00;
std::array<uint8_t, 8> Disassembler::singleRegister = {};
std::unique_ptr<MemoryBus> Disassembler::memoryBus = nullptr;

void Disassembler::execute(std::vector<uint8_t> &_rom) {
    Disassembler::memoryBus = std::make_unique<MemoryBus>();
    Disassembler::memoryBus->loadRom(std::move(_rom));

    while (true) {
        decode(Disassembler::memoryBus->loadMemory(programCounter));
    }
}

void Disassembler::decode(uint8_t operation) {
    printf("PC 0x%x - OP %x\n", programCounter, operation);

    programCounter++;

    switch (operation) {
        case 0x00:
            // No operation.
            break;
        case 0x31: {
            auto hi = load(programCounter);
            programCounter++;

            auto lo = load(programCounter);
            programCounter++;

            stackPointer = (lo << 8u) | hi;
            break;
        }
        case 0x3c:
            singleRegister[0x07]++;
            break;
        case 0x9c:
            // @TODO: Implement
            break;
        case 0xc3: {
            auto hi = load(programCounter);
            programCounter++;

            auto lo = load(programCounter);
            programCounter++;

            programCounter = (lo << 8u) | hi;
            break;
        }
        case 0xea:

            break;
        case 0xf3:
            // @TODO: Handle interrupts
            break;
//        case 0xc9:
            // @TODO: Implement

//            programCounter++;
//            break;
        default:
            throw std::runtime_error("Unimplemented opcode");
    }
}

uint8_t Disassembler::load(uint16_t index) {
    return Disassembler::memoryBus->loadMemory(index);
}
