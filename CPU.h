//
// Created by Christian aan de Wiel on 08/03/2021.
//

#ifndef GB_EMULATOR_CPU_H
#define GB_EMULATOR_CPU_H

#include "MemoryBus.h"

class CPU {
public:
    explicit CPU(const std::shared_ptr<MemoryBus> &_memoryBus) {
        this->memoryBus = _memoryBus;
    }
    void run();
    void executeOperation(uint8_t operation);
private:
    uint8_t loadFromMemoryBus();
    uint8_t loadFromMemoryBus(uint16_t address);
    uint8_t loadNextByte();
    uint16_t loadNextWord();
    void storeMemory(uint16_t address, uint8_t value);
    void pushToStack(uint16_t value);
    uint16_t popFromStack();

    std::weak_ptr<MemoryBus> memoryBus;

    // Based on: https://cturt.github.io/cinoop.html
    struct {
        struct {
            union {
                struct {
                    uint8_t f;
                    uint8_t a;
                };
                uint16_t af = 0x00b0;
            };
        };
        struct {
            union {
                struct {
                    uint8_t c;
                    uint8_t b;
                };
                uint16_t bc;
            };
        };
        struct {
            union {
                struct {
                    uint8_t e;
                    uint8_t d;
                };
                uint16_t de;
            };
        };
        struct {
            union {
                struct {
                    uint8_t l;
                    uint8_t h;
                };
                uint16_t hl;
            };
        };

        uint16_t stackPointer = 0xfffe;
        uint16_t programCounter = 0x0100;

        void setZeroFlag(bool flag) { flag ? this->f |= 1 << 7 : this->f &= ~(1 << 7); }
        void setSubtractFlag(bool flag) { flag ? this->f |= 1 << 6 : this->f &= ~(1 << 6); }
        void setHalfCarryFlag(bool flag) { flag ? this->f |= 1 << 5 : this->f &= ~(1 << 5); }
        void setCarryFlag(bool flag) { flag ? this->f |= 1 << 4 : this->f &= ~(1 << 4); }

        bool isZeroFlagSet() { return this->f & (1 << 7); }
        bool isSubtractFlagSet() { return this->f & (1 << 6); }
        bool isHalfCarryFlagSet() { return this->f & (1 << 5); }
        bool isCarryFlagSet() { return this->f & (1 << 4); }
    } registers;
};


#endif //GB_EMULATOR_CPU_H
