# Digital Electronics Theory Project
### SY Instrumentation and Control AY 2023-24

Project members:
- Param Dandekar - 612209010
- Sanika Jogipethkar - 612209021

## Emulation of an 8-bit microprocessor (PS-1021)

This project aims to design and emulate the working of a simple 8-bit processor, with a primary focus on understanding and implementing digital logic principles and a secondary focus on assembly language programming.

### Basic architecture

The architecture of the PS-1021 is based on classic 8-bit CPUs such as the Intel 8085. There are three general purpose registers (A, B, C), one address register (M), one flag register (F), one instruction register (IR), and one program counter (PC). All registers are 8-bit except IR and PC which are 16-bit. The processor is able to address up to 256 bytes of memory.

<!-- How much memory can be addressed might change? M could be split into H and L, then 64 kilobytes could be addressed. -->

#### Flags

There are 3 flags in the flag register:

| Flag  | Bit | Description                         |
| ----- | --- | ----------------------------------- |
| Zero  | 0   | 1 if reg A value is 00              |
| Carry | 1   | 1 if an overflow occurs when adding |
| Sign  | 2   | 1 if the number is negative         |

#### Instruction set

| Code | Mnemonic | Description  |
| ---- | -------- | ------------ |

- `MOV`: Copies data from one location to another. Both the source and destination can be either one of the four registers A, B, C, or M; or a memory address. The last four bits in the operand are used to select the source and destination registers:
    testing indentation


Used to select the source (bits 2 & 3) and destination (bits 0 & 1) registers. If bit 4 is set, moves to (if bit 5 is 0) or from (if bit 5 is 1) the memory address in M.

### Emulation

