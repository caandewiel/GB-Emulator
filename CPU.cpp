//
// Created by Christian aan de Wiel on 08/03/2021.
//

#include "CPU.h"

void CPU::run() {
    while (true) {
        executeOperation(loadFromMemoryBus());
    }
}

void CPU::executeOperation(uint8_t operation) {
    printf("| PC 0x%04x | OP 0x%02x | ", this->registers.programCounter, operation);
    printf("AF: %04x | BC: %04x | DE: %04x | HL: %04x | SP: %04x | PC: %04x |\n", this->registers.af, this->registers.bc,
           this->registers.de, this->registers.hl, this->registers.stackPointer,
           this->registers.programCounter);

    this->registers.programCounter++;

    switch (operation) {
        case 0x00:
            // No operation.
            break;
        case 0x01:
            this->registers.bc = loadNextWord();
            break;
        case 0x03:
            this->registers.bc++;
            break;
        case 0x18:
            this->registers.programCounter += loadNextByte();
            break;
        case 0x21:
            this->registers.hl = loadNextWord();
            break;
        case 0x23:
            this->registers.hl++;
            break;
        case 0x28: {
            auto value = loadNextByte();

            if (this->registers.isZeroFlagSet()) {
                this->registers.programCounter += value;
            }

            break;
        }
        case 0x2a:
            this->registers.a = this->registers.hl;
            this->registers.hl++;
            break;
        case 0x31:
            this->registers.stackPointer = loadNextWord();
            break;
        case 0x3c:
            this->registers.a++;
            this->registers.setSubtractFlag(false);
            break;
        case 0x3e:
            this->registers.a = loadNextByte();
            break;
        case 0x78:
            this->registers.a = this->registers.b;
            break;
        case 0x7c:
            this->registers.a = this->registers.h;
            break;
        case 0x7d:
            this->registers.a = this->registers.l;
            break;
        case 0xb1:
            this->registers.a |= this->registers.c;
            this->registers.setZeroFlag(this->registers.a == 0);
            this->registers.setSubtractFlag(false);
            this->registers.setHalfCarryFlag(false);
            this->registers.setCarryFlag(false);
            break;
        case 0xc3:
            this->registers.programCounter = loadNextWord();
            break;
        case 0xc5:
            this->pushToStack(this->registers.bc);
            break;
        case 0xc9:
            this->registers.programCounter = popFromStack();
            break;
        case 0xcd: {
            auto value = loadNextWord();
            pushToStack(this->registers.programCounter);
            this->registers.programCounter = value;
            break;
        }
        case 0xe0: {
            storeMemory(0xff00 + loadNextByte(), this->registers.a);
            break;
        }
        case 0xe1:
            this->registers.hl = popFromStack();
            break;
        case 0xe5:
            pushToStack(this->registers.hl);
            break;
        case 0xea:
            storeMemory(loadNextWord(), this->registers.a);
            break;
        case 0xf0:
            this->registers.a = loadFromMemoryBus(0xff00 + loadNextByte());
            break;
        case 0xf1:
            this->registers.af = popFromStack();
            break;
        case 0xf3:
            // @TODO: Handle interrupts
            break;
        case 0xf5:
            pushToStack(this->registers.af);
            break;
        default:
            printf("AF: %x \nBC: %x \nDE: %x \nHL: %x\nSP: %x\nPC: %x\n", this->registers.af, this->registers.bc,
                   this->registers.de, this->registers.hl, this->registers.stackPointer,
                   this->registers.programCounter);
            throw std::runtime_error("Unimplemented opcode");
    }
}

uint8_t CPU::loadFromMemoryBus() {
    return this->memoryBus.lock()->loadMemory(this->registers.programCounter);
}

uint8_t CPU::loadFromMemoryBus(uint16_t address) {
    return this->memoryBus.lock()->loadMemory(address);
}

uint16_t CPU::loadNextWord() {
    auto hi = this->loadFromMemoryBus();
    this->registers.programCounter++;

    auto lo = this->loadFromMemoryBus();
    this->registers.programCounter++;

    return (lo << 8u) | hi;
}

void CPU::storeMemory(uint16_t address, uint8_t value) {
    this->memoryBus.lock()->storeMemory(address, value);
}

uint8_t CPU::loadNextByte() {
    auto by = this->loadFromMemoryBus();
    this->registers.programCounter++;

    return by;
}

void CPU::pushToStack(uint16_t value) {
    this->registers.stackPointer--;
    storeMemory(this->registers.stackPointer, static_cast<uint8_t>(value >> 8));
    this->registers.stackPointer--;
    storeMemory(this->registers.stackPointer, static_cast<uint8_t>(value));
}

uint16_t CPU::popFromStack() {
    auto hi = loadFromMemoryBus(this->registers.stackPointer);
    this->registers.stackPointer++;
    auto lo = loadFromMemoryBus(this->registers.stackPointer);
    this->registers.stackPointer++;

    return (lo << 8u) | hi;
}
