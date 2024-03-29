#include <stdio.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "PS1021.h"
#include "assembler.h"

Processor readProgram(Processor p) {
    // Open the binary file in binary mode
    std::ifstream file("program.bin", std::ios::binary);

    // Check if the file was opened successfully
    if (!file) {
        std::cerr << "Cannot open file!" << std::endl;
        return p;
    }

    // Seek to the end of the file to find its size
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Create a vector to store the bytes
    std::vector<char> buffer(fileSize);

    // Read the bytes from the file into the buffer
    file.read(buffer.data(), fileSize);

    for (int i = 0; i < fileSize; i++) {
        p.writeInstruction(PROGRAM_START_ADDR + i, buffer[i]);
        i++;
        p.writeInstruction(PROGRAM_START_ADDR + i, buffer[i]);
    }

    // Close the file
    file.close();

    // Now buffer contains the bytes from the file
    // You can access the bytes using buffer[index]

    return p;
}

int main() {
    
    assemble();

    Processor p = Processor();

    p = readProgram(p);

    p.run(100);

    return 0;
}
