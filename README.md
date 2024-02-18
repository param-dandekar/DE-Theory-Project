# Digital Electronics Theory Project
### SY Instrumentation and Control AY 2023-24

Project members:
- Param Dandekar - 612209010
- Sanika Jogipethkar - 612209021

## Emulation of a rudimentary 8-bit microprocessor (PS-1021)

This project aims to design and emulate the working of a rudimentary 8-bit processor, with a primary focus on understanding and implementing digital logic principles and a secondary focus on assembly language programming.

### Basic architecture

The architecture of the PS-1021 is based on classic 8-bit CPUs such as the Intel 8085. There are three general purpose registers (A, B, C), one address register (AR), one flag register (FR), one instruction register (IR), and one program counter (PC). All registers are 8-bit except IR and PC which are 16-bit.

#### Instruction set

There are 16 instructions. Each instruction can be split into a number of microinstructions. The list of all microinstructions is:

| Code | Description                                  |
| :--: | :------------------------------------------: |
| IC   | Increment program counter                    |
| SU   | Enable subtraction                           |
| ZE   | If zero flag is 0, increment program counter |
| RA   | Write from reg A to bus                      |
| RB   | Write from reg B to bus                      |
| RC   | Write from reg C to bus                      |
| RM   | Write from memory to bus                     |
| IR   | Write from instruction register to bus       |
| AR   | Write from address register to bus           |
| CR   | Write from program counter to bus            |
| LR   | Write from ALU to bus                        |
| WA   | Write from bus to reg A                      |
| WB   | Write from bus to reg B                      |
| WC   | Write from bus to reg C                      |
| WM   | Write from bus to memory address             |
| IW   | Write from bus to instruction register       |
| AW   | Write from bus to address register           |
| CW   | Write from bus to program counter            |

The instructions along with their respective microinstructions are:

| Mnemonic   | Code | Description                | Microinstructions       |
| :--------: | :--: | :------------------------: | :---------------------: |
| NOP        | 0000 | No operation               | IC                      |
| LDA <addr> | 0001 | Load from <addr> to reg A  | IR AW; RM WA; IC        |
| LDB <addr> | 0010 | Load from <addr> to reg B  | IR AW; RM WB; IC        |
| LDC <addr> | 0011 | Load from <addr> to reg C  | IR AW; RM WC; IC        |
| LDIA <val> | 0100 | Load <val> into reg A      | IR WA; IC               |
| LDIB <val> | 0101 | Load <val> into reg B      | IR WB; IC               |
| LDIC <val> | 0110 | Load <val> into reg C      | IR WC; IC               |
| STA <addr> | 0111 | Store from reg A to <addr> | IR AW; RA WM; IC        |
| STB <addr> | 1000 | Store from reg B to <addr> | IR AW; RB WM; IC        |
| STC <addr> | 1001 | Store from reg C to <addr> | IR AW; RC WM; IC        |
| ADD        | 1010 | Add reg B to reg A         | LR RA; IC               |
| SUB        | 1011 | Subtract reg B from reg A  | SU; LR RA; IC           |
| JMP <val>  | 1100 | Set counter to <val>       | IR CW                   |
| JMPZ <val> | 1101 | Jump to <val> if zero      | ZE; IR CW               |
| SWP        | 1110 | Swap values in A and B     | RA AW; RB WA; AR WB; IC |
| SWPC       | 1111 | Swap values in A and C     | RA AW; RC WA; AR WC; IC |

For example, the instruction `LDA` to load a value from 

Note that the swap instructions overwrite the address register.