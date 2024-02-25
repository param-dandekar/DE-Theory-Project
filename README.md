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

##### Addressing modes

Several instructions have to specify a source, destination, or both. Both the source and destination can be either one of the four registers A, B, C, or M; or a memory address. The operand byte (`O7` to `O4`) is used to select the source and destination registers; the next two bits are used when copying to or from memory:
- Registers A, B, C, and M are addressed as `00`, `01`, `10`, and `11` respectively.
- The first pair of bits (`O7` & `O6`) indicates the source register, while the second pair (`O5` & `O4`) indicates the destination.
- The third pair of bits indicates whether to copy to or from memory:
    - If `O3` is set, the source is specified by register M.
    - If `O2` is set, the destination is specified by register M.
    - If both are set, the source is specified by register M while the destination is specified by register B.


- `MOV`: Copies data from one location to another. The data in the destination is overwritten; the data in the source is not altered.

| Code | Mnemonic | Description  |
| ---- | -------- | ------------ |


### Emulation

