#include "PS1021.h"

void Memory::initialise() {
    for (long i = 0; i < MAX_MEMORY; i++) {
        this->data[i] = 0x00;
    }
}


Memory m = Memory();
