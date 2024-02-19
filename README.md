# Digital Electronics Theory Project
### SY Instrumentation and Control AY 2023-24

Project members:
- Param Dandekar - 612209010
- Sanika Jogipethkar - 612209021

## Emulation of a rudimentary 8-bit microprocessor (PS-1021)

This project aims to design and emulate the working of a rudimentary 8-bit processor, with a primary focus on understanding and implementing digital logic principles and a secondary focus on assembly language programming.

### Basic architecture

The architecture of the PS-1021 is based on classic 8-bit CPUs such as the Intel 8085. There are three general purpose registers (A, B, C), one address register (AR), one flag register (FR), one instruction register (IR), and one program counter (PC). All registers are 8-bit except IR and PC which are 16-bit. The processor is able to address up to 256 bytes of RAM.

#### Instruction set

There are 16 instructions. Each instruction can be split into a number of microinstructions. The list of all microinstructions is:

| Code | Description                                  |
| ---- | -------------------------------------------- |
| IC   | Increment program counter                    |
| SU   | Enable subtraction                           |
| ZE   | Conditional jump                             |
| RA   | Write from reg A to bus                      |
| RB   | Write from reg B to bus                      |
| RC   | Write from reg C to bus                      |
| RM   | Write from memory to bus                     |
| IR   | Write from instruction register to bus       |
| AR   | Write from address register to bus           |
| LR   | Write from ALU to bus                        |
| WA   | Write from bus to reg A                      |
| WB   | Write from bus to reg B                      |
| WC   | Write from bus to reg C                      |
| WM   | Write from bus to memory address             |
| AW   | Write from bus to address register           |
| CW   | Write from bus to program counter            |

<!-- ZE: If zero flag is 0, write from instruction register to bus, else write from program counter -->

The instructions along with their respective microinstructions are:

| Mnemonic   | Code | Description                | Microinstructions       |
| ---------- | ---- | -------------------------- | ----------------------- |
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
| JMNZ <val> | 1101 | Jump to <val> if not zero  | ZE; IR CW               |
| SWP        | 1110 | Swap values in A and B     | RA AW; RB WA; AR WB; IC |
| SWPC       | 1111 | Swap values in A and C     | RA AW; RC WA; AR WC; IC |

For example, the instruction `LDA` to load a value from memory into register A is executed as follows:

1. `IR AW`: read data from instruction register onto bus, then write from bus onto address
2. `RM WA`: read data from the memory address in the address register and write it to register A
3. `IC`: increment the program counter

Note that the swap instructions overwrite the address register.

The first 4 bits of the instruction register hold the code for the instruction. The last 8 bits are used to pass addresses or values. Unused bits are set to zero. For example, the instruction to load data from memory address 112 into register A is `0001 0000 0110 0111` (or `1067` in hex).

##### Flags

| Flag  | Bit | Description                         |
| ----- | --- | ----------------------------------- |
| Zero  | 0   | 1 if reg A value is 00              |
| Carry | 1   | 1 if an overflow occurs when adding |
| Sign  | 2   | 1 if the number is negative         |
| Sub   | 3   | 1 if subtraction is in process      |


#### Emulation

