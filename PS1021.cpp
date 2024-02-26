#include <stdio.h>

#include "PS1021.h"
#include <iostream>
using namespace std;

Memory::Memory() {
    for (uint64_t i = 0; i < MAX_MEMORY; i++) {
        this->data[i] = 0x00;
    }
}

byte Memory::read(word address) {
    return this->data[address];
}

void Memory::write(word address, byte data) {
    this->data[address] = data;
}


int main() {
    
    Memory m = Memory();

    word addr = 0x0001;
    byte data = 0x60;

    m.write(addr, data);
    byte x = m.read(addr);

    return 0;

}