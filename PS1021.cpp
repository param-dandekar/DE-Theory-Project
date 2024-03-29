#include <stdio.h>

#include "PS1021.h"
#include <iostream>
using namespace std;

Memory::Memory() {
    clear();
}

byte * Memory::getMemory() {
    return memory;
}

void Memory::clear() {
    for (uint64_t i = 0; i < MAX_MEMORY; i++) {
        memory[i] = 0x00;
    }
}

byte Memory::read(word address) {
    return memory[address];
}

void Memory::write(word address, byte data) {
    memory[address] = data;
}

Processor::Processor() {
    resetComplete();
}

void Processor::resetComplete() {
    memory.clear();
    halted = false;
    PC = PROGRAM_START_ADDR;
    SP = 0xFFFF;
    A = 0x00;
    B = 0x00;
    C = 0x00;
    M = 0x00;
    flags = 0x00;
}

void Processor::fetchAndExecute() {
    byte nextInstructionCode = memory.read(PC++);
    byte nextInstructionData = memory.read(PC++);

    switch (nextInstructionCode)
    {
        case 0x00: MOV(nextInstructionData); break;
        case 0x01: MVI(nextInstructionData); break;
        case 0x02: LDA(nextInstructionData); break;
        case 0x03: LDB(nextInstructionData); break;
        case 0x04: LDC(nextInstructionData); break;
        case 0x05: LDM(nextInstructionData); break;
        case 0x06: STA(nextInstructionData); break;
        case 0x07: STB(nextInstructionData); break;
        case 0x08: STC(nextInstructionData); break;
        case 0x09: STM(nextInstructionData); break;
        case 0x0A: ADD(nextInstructionData); break;
        case 0x0B: ADC(nextInstructionData); break;
        case 0x0C: ADI(nextInstructionData); break;
        case 0x0D: ACI(nextInstructionData); break;
        case 0x0E: SUB(nextInstructionData); break;
        case 0x0F: SBB(nextInstructionData); break;
        case 0x10: SUI(nextInstructionData); break;
        case 0x11: SBI(nextInstructionData); break;
        case 0x12: INR(nextInstructionData); break;
        case 0x13: DCR(nextInstructionData); break;
        case 0x14: JMP(); break;
        case 0x15: JC(); break;
        case 0x16: JNC(); break;
        case 0x17: JP(); break;
        case 0x18: JNP(); break;
        case 0x19: JZ(); break;
        case 0x1A: JNZ(); break;
        case 0x1B: CMP(nextInstructionData); break;
        case 0x1C: CPI(nextInstructionData); break;
        case 0x1D: ANA(nextInstructionData); break;
        case 0x1E: ORA(nextInstructionData); break;
        case 0x1F: XRA(nextInstructionData); break;
        case 0x20: ANI(nextInstructionData); break;
        case 0x21: ORI(nextInstructionData); break;
        case 0x22: XRI(nextInstructionData); break;
        case 0x23: CMA(); break;
        case 0x24: STF(nextInstructionData); break;
        case 0x25: PUSH(nextInstructionData); break;
        case 0x26: POP(nextInstructionData); break;
        case 0x27: CALL(); break;
        case 0x28: RET(); break;
        case 0xFF: HALT(); break;
    }
}

void Processor::writeInstruction(word addr, byte ins) {
    memory.write(addr, ins);
}

void Processor::run(int n) {
    while (!halted && n--) {
        fetchAndExecute();
    }
}

byte * Processor::getRegister(byte referringBits) {
    switch (referringBits) {
        case 0b00: return &A; break;
        case 0b01: return &B; break;
        case 0b10: return &C; break;
        case 0b11: return &M; break;
        default: break;
    }
    throw invalid_argument("Invalid address specification");
}

byte * Processor::getSource(byte addressSpecifier) {
    if (addressSpecifier & 0b00001000) return memory.getMemory() + M;
    return getRegister(addressSpecifier >> 6);
}

byte * Processor::getDestination(byte addressSpecifier) {
    if (addressSpecifier & 0b00001100) return memory.getMemory() + B;
    if (addressSpecifier & 0b00000100) return memory.getMemory() + M;
    return getRegister((addressSpecifier >> 4) & 0b0011);
}

void Processor::setFlag(byte n, bool value) {
    if (value) flags |= 1 << n;
    else flags &= ~(1 << n);
}

void Processor::updateFlags(bool carry) {
    setFlag(0, !A);
    setFlag(1, carry);
    setFlag(2, A>>7);
}

void Processor::MOV(byte operand) {
    *getDestination(operand) = *getSource(operand);
}
void Processor::MVI(byte operand) {
    A = operand;
}

void Processor::LDA(byte operand) {
    A = memory.read(operand);
}
void Processor::LDB(byte operand) {
    B = memory.read(operand);
}
void Processor::LDC(byte operand) {
    C = memory.read(operand);
}
void Processor::LDM(byte operand) {
    M = memory.read(operand);
}

void Processor::STA(byte operand) {
    memory.write(operand, A);
}
void Processor::STB(byte operand) {
    memory.write(operand, B);
}
void Processor::STC(byte operand) {
    memory.write(operand, C);
}
void Processor::STM(byte operand) {
    memory.write(operand, M);
}

void Processor::ADD(byte operand) {
    ADI(*getSource(operand));
}
void Processor::ADC(byte operand) {
    ACI(*getSource(operand));
}
void Processor::ADI(byte operand) {
    word sum = A + operand;
    A = sum & 0xFF;
    updateFlags(sum >> 8);
}
void Processor::ACI(byte operand) {
    word sum = A + operand + flags&0b10;
    A = sum & 0xFF;
    updateFlags(sum >> 8);
}

void Processor::SUB(byte operand) {
    SUI(*getSource(operand));
}
void Processor::SBB(byte operand) {
    SBI(*getSource(operand));
}
void Processor::SUI(byte operand) {
    word sum = A + ~operand + 1;
    A = sum & 0xFF;
    updateFlags((sum >> 8));
}
void Processor::SBI(byte operand) {
    word sum = A + ~operand + 1 - flags&0b10;
    A = sum & 0xFF;
    updateFlags((sum >> 8));
}

void Processor::INR(byte operand) {
    (*getSource(operand))++;
    updateFlags(A >> 8);
}
void Processor::DCR(byte operand) {
    (*getSource(operand))--;
    updateFlags(A >> 8);
}

void Processor::JMP() {
    PC = ((B << 8) | M)*2 + PROGRAM_START_ADDR;
}
void Processor::JC() {
    if (flags&0b10) JMP();
}
void Processor::JNC() {
    if (!flags&0b10) JMP();
}
void Processor::JP() {
    if (!flags&0b100) JMP();
}
void Processor::JNP() {
    if (flags&0b100) JMP();
}
void Processor::JZ() {
    if (flags&0b1) JMP();
}
void Processor::JNZ() {
    if (!flags&0b1) JMP();
}

void Processor::CMP(byte operand) {
    CPI(*getSource(operand));
}
void Processor::CPI(byte operand) {
    setFlag(3, 0);
    setFlag(4, 0);
    setFlag(5, 0);

    if (operand > A) setFlag(3, 1);
    else if (operand == A) setFlag(4, 1);
    else setFlag(5, 1);
}

void Processor::ANA(byte operand) {
    ANI(*getSource(operand));
}
void Processor::ANI(byte operand) {
    A &= operand;
}

void Processor::ORA(byte operand) {
    ORI(*getSource(operand));
}
void Processor::ORI(byte operand) {
    A |= operand;
}

void Processor::XRA(byte operand) {
    XRI(*getSource(operand));
}
void Processor::XRI(byte operand) {
    A ^= operand;
}

void Processor::CMA() {
    A = ~A;
}

void Processor::STF(byte operand) {
    flags = operand;
}

void Processor::PUSH(byte operand) {
    byte *source = getSource(operand);
    memory.write(SP--, *getSource(operand));
}
void Processor::POP(byte operand) {
    *getDestination(operand) = memory.read(++SP);
}

void Processor::CALL() {
    memory.write(SP--, PC&0xFF);
    memory.write(SP--, PC>>8);
    JMP();
}
void Processor::RET() {
    B = memory.read(++SP);
    M = memory.read(++SP);
    JMP();
}

void Processor::HALT() {
    halted = true;
}

