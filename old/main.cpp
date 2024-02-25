#include <iostream>
#include <stdint.h>
#include <map>
using namespace std;

#include "compiler.h"

#define MEM_SIZE 0xFFFF
#define MAX_PROGRAM_SIZE 0xFFFF

class Processor {
    private:
        uint8_t  memory[MEM_SIZE];  // Memory
        uint8_t  bus    = 0x00;     // Bus
        uint8_t  regA   = 0x00;     // General registers
        uint8_t  regB   = 0x00;
        uint8_t  regC   = 0x00;
        uint8_t  addr   = 0x00;     // Address register
        uint8_t  regF   = 0x00;     // Flag register
        uint32_t regI   = 0x0000;   // Instruction register
        uint16_t PC     = 0x0000;   // Program counter
        uint8_t  ALU    = 0x00;     // ALU out
        
        uint32_t program[MAX_PROGRAM_SIZE];  // Program storage
    public:
        Processor() {
            printf("Creating processor...\n");
        }
        void print_info(bool detailed = false) {
            printf("Register A:\t%02X\n", regA);
            printf("Register B:\t%02X\n", regB);
            printf("Register C:\t%02X\n", regC);
            printf("Flags:\t\t%02X\n", regF);

            if (detailed) {
                printf("Address:\t%02X\n", addr);
                printf("Instruction:\t%04X\n", regI);
            }
        }

        void IC() { PC++; }
        void SU() { regF |= 0b1000; }
        void ZE() { if (regF & 0b0001) bus = PC; else IR(); }
        void RA() { bus = regA; }
        void RB() { bus = regB; }
        void RC() { bus = regC; }
        void RM() { bus = memory[addr]; }
        void IR() { bus = regI & 0xFF; }
        void AR() { bus = addr; }
        void LR() { bus = ALU; }
        void WA() { regA = bus; }
        void WB() { regB = bus; }
        void WC() { regC = bus; }
        void WM() { memory[addr] = bus; }
        void AW() { addr = bus; }
        void CW() { PC = bus; }

        void NOP()  { IC(); }
        void LDA()  { IR(); AW(); RM(); WA(); IC(); }
        void LDB()  { IR(); AW(); RM(); WB(); IC(); }
        void LDC()  { IR(); AW(); RM(); WC(); IC(); }
        void LDIA() { IR(); WA(); IC(); }
        void LDIB() { IR(); WB(); IC(); }
        void LDIC() { IR(); WC(); IC(); }
        void STA()  { IR(); AW(); RA(); ; WM(); IC(); }
        void STB()  { IR(); AW(); RB(); WM(); IC(); }
        void STC()  { IR(); AW(); RC(); WM(); IC(); }
        // void ADD()  { LR(); WA(); IC(); }
        void ADD()  { regA += regB; IC(); }
        // void SUB()  { SU(); LR(); WA(); IC(); }
        void SUB()  { regA -= regB; IC(); }
        void JMP()  { IR(); CW(); }
        void JMNZ() { ZE(); CW(); }
        void SWP()  { RA(); AW(); RB(); WA(); AR(); WB(); IC(); }
        void SWPC() { RA(); AW(); RC(); WA(); AR(); WC(); IC(); }

        int cycle() {
            if (PC == 0xFFFF) {
                return 1;
            }

            regI = program[PC];
            regF &= 0b0111;

            // uint8_t ALUin = (regF >> 3) ? !regB : regB;

            // ALU = regA + ALUin;
            if (!regA) regF |= 0b0001;
            else regF &= 0b1110;
             
            switch (uint8_t instruction_code = (regI >> 12)) {
                case 0x0: NOP(); break;
                case 0x1: LDA(); break;
                case 0x2: LDB(); break;
                case 0x3: LDC(); break;
                case 0x4: LDIA(); break;
                case 0x5: LDIB(); break;
                case 0x6: LDIC(); break;
                case 0x7: STA(); break;
                case 0x8: STB(); break;
                case 0x9: STC(); break;
                case 0xA: ADD(); break;
                case 0xB: SUB(); break;
                case 0xC: JMP(); break;
                case 0xD: JMNZ(); break;
                case 0xE: SWP(); break;
                case 0xF: SWPC(); break;
                default: break;
            }

            return 0;
        }

        void load_program(string program_file_name) {
            // int i = 0;
            // for (uint32_t *p = program_in; *p; p++) {
            //     program[i++] = *p;
            // }

            ifstream program_file((program_file_name+".bin").c_str());
            int i = 0;
            string current_line;
            uint64_t next_instruction;
            
            while (getline(program_file, current_line)) {
                program[i++] = std::stoul(current_line, nullptr, 10);
            }

        }

        int get_counter() {
            return PC;
        }

        void debug() {
            printf("ins: %04X A: %02X B: %02X C: %02X memory: %02X %02X %02X\n", regI, regA, regB, regC, memory[0], memory[1], memory[2]);
        }
};

int main() {
    string program_file_name = "test_program";
    assemble(program_file_name, "txt");

    Processor p;
    // p.print_info(true);

    int line = 0;
    int max_it = 40;
    
    p.load_program(program_file_name);

    while (line < max_it) {
        // cout << p.get_counter() << endl;
        line++;
        p.debug();
        cout << "-----------" << endl;
        if (p.cycle()) break;
    }
    p.debug();
    cout << line << endl;
    return 0;
}