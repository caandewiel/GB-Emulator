//
// Created by Christian aan de Wiel on 08/03/2021.
//

#include "GameBoy.h"

void GameBoy::loadRom(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    file.unsetf(std::ios::skipws);
    std::streampos fileSize;

    if (!file) {
        throw std::runtime_error("Could not loadFromMemoryBus rom");
    }

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> content;
    content.reserve(fileSize);

    content.insert(content.begin(), std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>());

    this->memoryBus->loadRom(std::move(content));
}

GameBoy::GameBoy() {
    this->memoryBus = std::make_shared<MemoryBus>();
    this->cpu = std::make_unique<CPU>(this->memoryBus);
}

void GameBoy::run() {
    this->cpu->run();
}
