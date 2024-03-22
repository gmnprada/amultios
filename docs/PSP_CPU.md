# Amultios
Yet Another PSP Documentation From Various Source To Finish Emulator Development

# RISC Overview

The RISC (Reduced Instruction Set Computer) architecture is a type of computer architecture with a simple and small set of instructions that are optimized to execute in a single clock cycle. The RISC architecture is designed to be faster, simpler, and more efficient than CISC (Complex Instruction Set Computer) architecture. Here is a brief overview of the RISC core instruction set:

Load and Store Instructions:
lw (load word): loads a 32-bit word from memory
lh (load halfword): loads a 16-bit halfword from memory
lb (load byte): loads an 8-bit byte from memory
sw (store word): stores a 32-bit word to memory
sh (store halfword): stores a 16-bit halfword to memory
sb (store byte): stores an 8-bit byte to memory
Arithmetic and Logical Instructions:
add: adds two registers and stores the result in a register
addi: adds a register and a signed immediate value and stores the result in a register
sub: subtracts two registers and stores the result in a register
and: performs a logical AND operation on two registers and stores the result in a register
or: performs a logical OR operation on two registers and stores the result in a register
xor: performs a logical XOR operation on two registers and stores the result in a register
sll: shifts a register left by a specified number of bits and stores the result in a register
srl: shifts a register right (with zero extension) by a specified number of bits and stores the result in a register
sra: shifts a register right (with sign extension) by a specified number of bits and stores the result in a register
Control Flow Instructions:
j (jump): jumps to a specified memory address
jal (jump and link): jumps to a specified memory address and stores the return address in a register
jr (jump register): jumps to a specified memory address contained in a register
jalr (jump and link register): jumps to a specified memory address contained in a register and stores the return address in a register
beq (branch if equal): branches to a specified memory address if two registers are equal
bne (branch if not equal): branches to a specified memory address if two registers are not equal
Comparison Instructions:
slt (set less than): sets a register to 1 if one register is less than another, 0 otherwise
slti (set less than immediate): sets a register to 1 if a register is less than a signed immediate value, 0 otherwise
Other Instructions:
lui (load upper immediate): loads a 16-bit immediate value into the upper half of a register and zeroes the lower half
nop (no operation): does nothing

These instructions are the basic building blocks of the RISC architecture and are used to perform a wide range of tasks. By keeping the instruction set small and simple, RISC processors can achieve high performance with relatively low power consumption.

# The MipsInstruction 
represents a set of instructions for the MIPS-I and MIPS-II architectures that are combined into a single list. These instructions include operations for arithmetic, logical, memory, branch, jump, and system calls.

Here is a brief description of some of the instruction categories:

Arithmetic instructions perform mathematical operations on registers, such as adding, subtracting, multiplying, and dividing. 
Examples include ADD, ADDI, ADDIU, ADDU, DIV, DIVU, MULT, and MULTU.

Logical instructions perform logical operations on registers, such as bitwise AND, OR, and XOR. 
Examples include AND, ANDI, NOR, OR, ORI, XOR, and XORI.

Memory instructions load or store data in memory. 
Examples include LB, LBU, LH, LHU, LUI, LW, SB, SH, and SW.

Branch instructions test conditions and perform conditional jumps or branches. 
Examples include BEQ, BGEZ, BGTZ, BLEZ, BLTZ, BNE, BC1F, and BC1T.

Jump instructions transfer control to a specified address. 
Examples include J, JAL, JALR, and JR.

System call instructions transfer control to the operating system to perform various tasks, such as input/output and process management. The SYSCALL instruction is used for this purpose.
These instructions operate on registers, which are 32-bit storage locations that can hold data or addresses. The instructions use different addressing modes, such as immediate, register, and offset addressing, to access operands and memory locations.

# PSP CPU Known as Tachyon

Mips Instruction Set is Based on Mips I Mips 2 Instruction Set With Allegrex Instruction 