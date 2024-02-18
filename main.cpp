#include <iostream>
#include <stdint.h>
using namespace std;

class Processor {
    static const uint8_t MEM_SIZE = 0xff;
    private:
        uint8_t  memory[MEM_SIZE];   // Memory
        uint8_t  regA = 0x00;        // General registers
        uint8_t  regB = 0x00;
        uint8_t  regC = 0x00;
        uint8_t  regD = 0x00;
        uint8_t  FR   = 0x00;        // Flag register
        uint16_t IR   = 0x00;        // Instruction register
    public:
        Processor() {
            printf("Creating processor...\n");
        }
        int print_info() {
            printf("Register A:\t%02X\n", regA);
            printf("Register B:\t%02X\n", regB);
            printf("Register C:\t%02X\n", regC);
            printf("Register D:\t%02X\n", regD);
            printf("Flags:\t\t%02X\n", regD);
            return 0;
        }
};

int main() {
    Processor p;
    p.print_info();



    return 0;
}