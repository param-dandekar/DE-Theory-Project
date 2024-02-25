#include <cstdint>

typedef uint8_t byte;
typedef uint16_t word;

// A class representing the memory for the processor
class Memory {
    private:
        static const uint64_t MAX_MEMORY = 0xFFFF;
        byte data[MAX_MEMORY];

    public:
        // Initialise data in all memory addresses to 0
        void initialise();

        // Read the data at a particular memory address
        byte read(byte address);

        // Write data to a particular memory address
        void write(byte address, byte data);
};

// A class representing the processor
class Processor {
    private:
    // Program counter
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

    public:
    // Reset all registers and memory
    void resetComplete();

    // Fetch the next instruction
    void fetch();

    // Execute the current instruction
    void execute();

    // Run for n cycles; if n is -1, keep running until last instruction
    void run(int n);

    // Copy data from source to destination
    void MOV();
    // Copy operand to accumulator
    void MVI();
    // Load data from memory to accumulator
    void LDA();
    // Load data from memory to register B
    void LDB();
    // Load data from memory to register C
    void LDC();
    // Load data from memory to register M
    void LDM();
    // Store data to memory from accumulator
    void STA();
    // Store data to memory from register B
    void STB();
    // Store data to memory from register C
    void STC();
    // Store data to memory from register M
    void STM();
    // Add source to accumulator
    void ADD();
    // Add source to accumulator with carry
    void ADC();
    // Add operand to accumulator
    void ADI();
    // Add operand to accumulator with carry
    void ACI();
    // Subtract source from accumulator
    void SUB();
    // Subtract source from accumulator with carry
    void SBB();
    // Subtract operand from accumulator
    void SUI();
    // Subtract operand from accumulator with carry
    void SBI();
    // Increment data in destination
    void INR();
    // Decrement data in destination
    void DCR();
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
    void CMP();
    // Compare operand with accumulator
    void CPI();
    // AND source and accumulator
    void ANA();
    // OR source and accumulator
    void ORA();
    // XOR source and accumulator
    void XRA();
    // AND operand and accumulator
    void ANI();
    // OR operand and accumulator
    void ORI();
    // XOR operand and accumulator
    void XRI();
    // Complement accumulator
    void CMA();
    // Set flag register to operand
    void STF();
    // Push source onto stack
    void PUSH();
    // Pop from stack to destination
    void POP();
    // Call subroutine by operand
    void CALL();
    // Return
    void RET();
    // Halt program
    void HALT();

};