#include <cstdint>

typedef uint8_t byte;
typedef uint16_t word;

static const uint16_t PROGRAM_START_ADDR = 0x2000;

// A class representing the memory for the processor
class Memory {
    private:
    static const uint64_t MAX_MEMORY = 0xFFFF;
    byte memory[MAX_MEMORY];

    public:
    // Constructor
    Memory();

    // Get a pointer to the memory values
    byte * getMemory();

    // Clear all data
    void clear();

    // Read the data at a particular memory address
    byte read(word address);

    // Write data to a particular memory address
    void write(word address, byte data);
};

// A class representing the processor
class Processor {
    private:
    // True if the processor is halted, false otherwise
    bool halted;

    // Program counter; starts at address 0x00FF
    word PC;
    // Stack pointer
    word SP;

    // General-purpose registers
    byte A, B, C;
    // Memory register
    byte M;

    // Flag register
    // | Bit | Flag     |
    // | :-- | :------- |
    // | B0  | Zero     |
    // | B1  | Carry    |
    // | B2  | Sign     |
    // | B3  | Less     |
    // | B4  | Equal    |
    // | B5  | Greater  |
    // | B6  | N/A      |
    // | B7  | N/A      |
    byte flags;

    // Memory of the processor
    Memory memory;

    // Fetch and execute the next instruction; decrement the number of instructions
    void fetchAndExecute();

    // Set or clear bit n of flag register
    void setFlag(byte n, bool value);

    // Update flags according to the data in register A
    void updateFlags(bool carry); 
    
    // Get referred register from appropriate bits of operand
    byte * getRegister(byte referringBits);

    // Get source from operand
    byte * getSource(byte addressingMode);

    // Get destination from operand
    byte * getDestination(byte addressingMode);

    public:
    // Constructor
    Processor();

    // Reset all registers and memory
    void resetComplete();

    // Write instruction to memory
    void writeInstruction(word addr, byte ins);

    // Run n instructions
    void run(int n);

    // Copy data from source to destination
    void MOV(byte operand);
    // Copy operand to accumulator
    void MVI(byte operand);
    // Load data from memory to accumulator
    void LDA(byte operand);
    // Load data from memory to register B
    void LDB(byte operand);
    // Load data from memory to register C
    void LDC(byte operand);
    // Load data from memory to register M
    void LDM(byte operand);
    // Store data to memory from accumulator
    void STA(byte operand);
    // Store data to memory from register B
    void STB(byte operand);
    // Store data to memory from register C
    void STC(byte operand);
    // Store data to memory from register M
    void STM(byte operand);
    // Add source to accumulator
    void ADD(byte operand);
    // Add source to accumulator with carry
    void ADC(byte operand);
    // Add operand to accumulator
    void ADI(byte operand);
    // Add operand to accumulator with carry
    void ACI(byte operand);
    // Subtract source from accumulator
    void SUB(byte operand);
    // Subtract source from accumulator with carry
    void SBB(byte operand);
    // Subtract operand from accumulator
    void SUI(byte operand);
    // Subtract operand from accumulator with carry
    void SBI(byte operand);
    // Increment data in destination
    void INR(byte operand);
    // Decrement data in destination
    void DCR(byte operand);
    // Jump unconditionally
    void JMP();
    // Jump if carry
    void JC();
    // Jump if not carry
    void JNC();
    // Jump if not sign
    void JP();
    // Jump if sign
    void JNP();
    // Jump if zero
    void JZ();
    // Jump if not zero
    void JNZ();
    // Compare source with accumulator
    void CMP(byte operand);
    // Compare operand with accumulator
    void CPI(byte operand);
    // AND source and accumulator
    void ANA(byte operand);
    // OR source and accumulator
    void ORA(byte operand);
    // XOR source and accumulator
    void XRA(byte operand);
    // AND operand and accumulator
    void ANI(byte operand);
    // OR operand and accumulator
    void ORI(byte operand);
    // XOR operand and accumulator
    void XRI(byte operand);
    // Complement accumulator
    void CMA();
    // Set flag register to operand
    void STF(byte operand);
    // Push source onto stack
    void PUSH(byte operand);
    // Pop from stack to destination
    void POP(byte operand);
    // Call subroutine
    void CALL();
    // Return
    void RET();
    // Halt program
    void HALT();

};