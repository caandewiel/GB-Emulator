//
// Created by Christian aan de Wiel on 03/03/2021.
//
#include <iostream>
#include <fstream>

int main() {
    std::ifstream readFile("/Users/christian/GB-Emulator/instr_timing.gb", std::ios::out | std::ios::binary);

    if (!readFile) {
        throw std::runtime_error("Could not load rom");
    }

    readFile.seekg(0, std::ios::end);
    auto length = readFile.tellg();
    readFile.seekg(0, std::ios::beg);

    char* buffer;
    buffer = new char[length];

    readFile.read(buffer, length);
    readFile.close();

    std::cout << "Read ROM" << std::endl;
}

