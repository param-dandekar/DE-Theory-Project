#include <iostream>
using namespace std;
#include <stdint.h>



class Processor {
    static const uint8_t MEM_SIZE = 0xff;
    private:
        uint8_t  memory[MEM_SIZE];  // Memory
        uint8_t  bus  = 0x00;       // Bus
        uint8_t  regA = 0x00;       // General registers
        uint8_t  regB = 0x00;
        uint8_t  regC = 0x00;
        uint8_t  AR   = 0x00;       // Address register
        uint8_t  FR   = 0x00;       // Flag register
        uint16_t IR   = 0x00;       // Instruction register
        uint16_t PC   = 0x00;       // Program counter
    public:
        Processor() {
            printf("Creating processor...\n");
        }
        int print_info(bool detailed = false) {
            printf("Register A:\t%02X\n", regA);
            printf("Register B:\t%02X\n", regB);
            printf("Register C:\t%02X\n", regC);
            printf("Flags:\t\t%02X\n", FR);

            if (detailed) {
                printf("Address:\t%02X\n", AR);
                printf("Instruction:\t%02X\n", IR);
            }
            return 0;
        }

};

int main() {
    Processor p;
    p.print_info(true);



    return 0;
}