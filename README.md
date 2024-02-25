# Digital Electronics Theory Project
### SY Instrumentation and Control AY 2023-24

Project members:
- Param Dandekar - 612209010
- Sanika Jogipethkar - 612209021

## Emulation of an 8-bit microprocessor (PS-1021)

This project aims to design and emulate the working of a simple 8-bit processor, with a primary focus on understanding and implementing digital logic principles and a secondary focus on assembly language programming.

### Basic architecture

The architecture of the PS-1021 is based on classic 8-bit CPUs such as the Intel 8085. There are three general purpose registers (A or accumulator, B, C), one address register (M), one flag register (F), one instruction register (IR), and one program counter (PC). All registers are 8-bit except IR and PC which are 16-bit.

The processor is able to address up to 256 bytes of memory at a time. .

<!-- How much memory can be addressed might change? M could be split into H and L, then 64 kilobytes could be addressed. -->

#### Flags

There are 3 flags in the flag register:

| Flag  | Bit | Description                         |
| ----- | --- | ----------------------------------- |
| Zero  | 0   | 1 if reg A value is 00              |
| Carry | 1   | 1 if an overflow occurs when adding |
| Sign  | 2   | 1 if the number is negative         |
| <     | 3   | Depends on result of comparison     |
| =     | 4   | Depends on result of comparison     |
| >     | 5   | Depends on result of comparison     |

#### Instructions

##### Addressing modes

Several instructions have to specify a source, destination, or both. Both the source and destination can be either one of the four registers A, B, C, or M; or a memory address. The operand byte (`O7` to `O4`) is used to select the source and destination registers; the next two bits are used when copying to or from memory:
- Registers A, B, C, and M are addressed as `00`, `01`, `10`, and `11` respectively.
- The first pair of bits (`O7` & `O6`) indicates the source register, while the second pair (`O5` & `O4`) indicates the destination.
- The third pair of bits indicates whether to copy to or from memory:
    - If `O3` is set, the source is specified by register M.
    - If `O2` is set, the destination is specified by register M.
    - If both are set, the source is specified by register M while the destination is specified by register B.

##### Instruction set

- `MOV`: Copies data from one **source** to **destination**. The data in the destination is overwritten; the data in the source is not altered.
- `MVI`: Copies the **operand** data to the accumulator.
- `LDA`: Loads data from a **memory address** (given as an operand) into the accumulator. Similarly, `LDB`, `LDC`, `LDM`.
- `STA`: Stores data from the accumulator into a **memory address**. Similarly, `STB`, `STC`, `STM`.
- `ADD`: Adds the **value** from a register or memory to the value in the accumulator. Modifies flags.
- `ADC`: 'Add with carry': first adds normally, then if the carry flag is set, increments the sum by 1. Modifies flags.
- `ADI`: Adds the **operand** to the accumulator. Modifies flags.
- `ACI`: Adds **operand** with carry. Modifies flags.
- `SUB`: Subtracts **source value** from accumulator. Modifies flags.
- `SBB`: Subtracts **source value** from accumulator with borrow. Modifies flags.
- `SUI`: Subtracts **operand** from accumulator. Modifies flags.
- `SBI`: Subtracts **operand** from accumulator with borrow. Modifies flags.
- `INR`: Increments **destination value** by 1.
- `DCR`: Decrements **destination value** by 1.
- `JMP`: Jump to a **memory address** unconditionally.
- `JC`: Jump if carry flag is set.
- `JNC`: Jump if carry flag is not set.
- `JP`: Jump if sign flag is not set.
- `JNP`: Jump if sign flag is set.
- `JZ`: Jump if zero flag is set.
- `JNZ`: Jump if zero flag is not set.
- `CMP`: Compares **value** to data in accumulator, and accordingly sets the comparison flags.
- `CPI`: Compares **operand** to data in accumulator.
- `ANA`: Performs logical `AND` on the contents of the accumulator and the **source value** (result stored in accumulator). Similarly, `ORA`, `XRA`.
- `ANI`: Performs logical `AND` on the contents of the accumulator and the **operand** (result stored in accumulator). Similarly, `ORI`, `XRI`.
- `CMA`: Complements the value in the accumulator.
- `STF`: Sets flags according to the **operand**.
- `PUSH`: The stack pointer is decremented and the **source value** is copied to the new location.
- `POP`: The data at the location pointed to by the stack pointer is copied to the **destination** and the stack pointer is incremented.
- `CALL`: The address of the next instruction is pushed onto the stack, and the program counter is set to the address specified by the **operand**.
- `RET`: The program counter is set to the address specified by the top byte of the stack.

A list of these instructions with opcodes and short descriptions is given below:

| Code | Mnemonic | Description                                  |
| ---- | -------- | -------------------------------------------- |
| 0x00 | MOV      | Copy data from source to destination         |
| 0x01 | MVI      | Copy operand to accumulator                  |
| 0x02 | LDA      | Load data from memory to accumulator         |
| 0x03 | LDB      | Load data from memory to register B          |
| 0x04 | LDC      | Load data from memory to register C          |
| 0x05 | LDM      | Load data from memory to register M          |
| 0x06 | STA      | Store data to memory from accumulator        |
| 0x07 | STB      | Store data to memory from register B         |
| 0x08 | STC      | Store data to memory from register C         |
| 0x09 | STM      | Store data to memory from register M         |
| 0x0A | ADD      | Add source to accumulator                    |
| 0x0B | ADC      | Add source to accumulator with carry         |
| 0x0C | ADI      | Add operand to accumulator                   |
| 0x0D | ACI      | Add operand to accumulator with carry        |
| 0x0E | SUB      | Subtract source from accumulator             |
| 0x0F | SBB      | Subtract source from accumulator with carry  |
| 0x10 | SUI      | Subtract operand from accumulator            |
| 0x11 | SBI      | Subtract operand from accumulator with carry |
| 0x12 | INR      | Increment data in destination                |
| 0x13 | DCR      | Decrement data in destination                |
| 0x14 | JMP      | Jump unconditionally                         |
| 0x15 | JC       | Jump if carry                                |
| 0x16 | JNC      | Jump if not carry                            |
| 0x17 | JP       | Jump if not sign                             |
| 0x18 | JNP      | Jump if sign                                 |
| 0x19 | JZ       | Jump if zero                                 |
| 0x1A | JNZ      | Jump if not zero                             |
| 0x1B | CMP      | Compare source with accumulator              |
| 0x1C | CPI      | Compare operand with accumulator             |
| 0x1D | ANA      | AND source and accumulator                   |
| 0x1E | ORA      | OR source and accumulator                    |
| 0x1F | XRA      | XOR source and accumulator                   |
| 0x20 | ANI      | AND operand and accumulator                  |
| 0x21 | ORI      | OR operand and accumulator                   |
| 0x22 | XRI      | XOR operand and accumulator                  |
| 0x23 | CMA      | Complement accumulator                       |
| 0x24 | STF      | Set flag register to operand                 |
| 0x25 | PUSH     | Push source onto stack                       |
| 0x26 | POP      | Pop from stack to destination                |
| 0x27 | CALL     | Call subroutine by operand                   |
| 0x28 | RET      | Return                                       |
| 0xFF | HALT     | Halt program                                 |

### Emulation

