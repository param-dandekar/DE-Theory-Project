# Digital Electronics Theory Project
### SY Instrumentation and Control AY 2023-24

Project members:
- Param Dandekar - 612209010
- Sanika Jogipethkar - 612209021

## Emulation of a rudimentary 8-bit microprocessor (PS-1021)

This project aims to design and emulate the working of a rudimentary 8-bit processor, with a primary focus on understanding and implementing digital logic principles and a secondary focus on assembly language programming.

### Basic architecture

The architecture of the PS-1021 is based on classic 8-bit CPUs such as the Intel 8085. There are three general purpose registers, one address register, one flag register, one instruction register, and one program counter. 

#### Instruction set

| Mnemonic   | Code | Description                |
| NOP        | 0000 | No operation               |
| LDA <addr> | 0001 | Load from <addr> to reg A  |
| LDB <addr> | 0010 | Load from <addr> to reg B  |
| LDC <addr> | 0011 | Load from <addr> to reg C  |
| LDIA <val> | 0100 | Load <val> into reg A      |
| LDIB <val> | 0101 | Load <val> into reg B      |
| LDIC <val> | 0110 | Load <val> into reg C      |
| STA <addr> | 0111 | Store from reg A to <addr> |
| STB <addr> | 1000 | Store from reg B to <addr> |
| STC <addr> | 1001 | Store from reg C to <addr> |
| ADD        | 1010 | Add reg B to reg A         |
| SUB        | 1011 | Subtract reg B from reg A  |
| JMP <val>  | 1100 | Set counter to <val>       |
| JMPZ <val> | 1101 | Jump to <val> if zero      |
| SWP        | 1110 | Swap values in A and B     |
| SWPC       | 1111 | Swap values in A and C     |
