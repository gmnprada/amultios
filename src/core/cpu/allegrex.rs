use bitflags::bitflags;

// MIPS-I , MIPS-II, MIPS-III Instruction Available on Allegrex
#[derive(Debug)]
#[repr(u8)]
enum MipsInstruction {
    /* Mips Instruction| Description                             |  */
    ADD,   /*          | Add                                     |  */
    ADDI,  /*          | Add Immediate                           |  */
    ADDIU, /*          | Add Immediate Unsigned                  |  */
    ADDU,  /*          | Add Unsigned                            |  */
    AND,   /*          | And                                     |  */
    ANDI,  /*          | And Immediate                           |  */
    BC1F,  /*          | Branch on FPU False                     |  */
    BC1FL, /*          | Branch on FPU False Likely              |  */
    BC1T,  
    BC1TL,
    BEQ,
    BEQL,
    BGETZ,
    BGETZL,
    BGEZ,
    BGEZAL,
    BGEZALL,
    BGEZL,
    BLEZ,
    BLEZL,
    BLTZ,
    BLTZAL,
    BLTZALL,
    BLTZL,
    BNE,
    BNEL,
    BREAK,
    CFC1,
    CTC1,
    DIV,
    DIVU,
    ERET,
    J,
    JAL,
    JALR,
    JR,
    LB,
    LBU,
    LH,
    LHU,
    LUI,
    LW,
    LWC1,
    LWL,
    LWR,
    MFC0,
    MFC1,
    MFHI,
    MFLO,
    MTHI,
    MTLO,
    MULT,
    MULTU,
    NOP,
    NOR,
    OR,
    ORI,
    SB,
    SH,
    SLL,
    SLLV,
    SLT,
    SLTI,
    SLTIU,
    SLTU,
    SRA,
    SRAV,
    SRL,
    SRLV,
    SUB,
    SUBU,
    SW,
    SWC1,
    SWL,
    SWR,
    SYSCALL,
    XOR,
    XORI,
}

bitflags! {
    //  Flags Static Value Mips Instruction Header 000000 6 bits length
    #[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
    struct MipsInstructionOp: u8 {
        // Bits Mask Value Of Op    OP         Syntax
        const ADD     = 0b000000;   // add     rd,rs,rt
        const ADDI    = 0b001000;   // addi    rt,rs,immediate
        const ADDIU   = 0b001001;   // addiu   rt,rs,immediate
        const ADDU    = 0b000000;   // addu    rd,rs,rt
        const AND     = 0b000001;   // and     rd,rs,rt
        const ANDI    = 0b001100;   // andi    rs,rt,immediate
        const BC1F    = 0b010001;   // bc1f    rd,rs,rt
        const BC1FL   = 0b010001;   // bc1fl   offset
        const BC1T    = 0b010001;   // bc1ft   offset
        const BC1TL   = 0b010001;   // bc1tl   offset
        const BEQ     = 0b000100;   // beq     rs,rt,offset
        const BEQL    = 0b010100;   // beql    rs,rt,offset
        const BGETZ   = 0b000111;   // bgetz
        const BGETZL  = 0b010111;   // bgetzl
        const BGEZ    = 0b000001;   // bgez    rs,offset
        const BGEZAL  = 0b000001;   // bgezal
        const BGEZALL = 0b000001;   // bgezall
        const BGEZL   = 0b000001;   // 
        const BLEZ    = 0b000110;
        const BLEZL   = 0b010110;
        const BLTZ    = 0b000001;
        const BLTZAL  = 0b000001;
        const BLTZALL = 0b000001;
        const BLTZL   = 0b000001;
        const BNE     = 0b000101;
        const BNEL    = 0b010101;
        const BREAK   = 0b000000;
        const CFC1    = 0b010001;
        const CTC1    = 0b010001;
        const DIV     = 0b000011;
        const DIVU    = 0b000011;
        const ERET    = 0b010000;
        const J       =         ;
        const JAL     =         ;
        const JALR    =         ;
        const JR      =         ;
        const LB      =         ;
        const LBU     =         ;
        const LH      =         ;
        const LHU     =         ;
        const LUI     =         ;

    }
}


// Special Psp Allegrex Instruction TM
// I = Independent Instruction , D = Data
enum AllegrexInstruction {
    BITREV, // Bit Reverse
    CACHE,  // Index Invalidate (I)
    CACHE,  // Index Unlock (I)
    CACHE,  // Hit Invalidate (I)
    CACHE,  // Fill (I)
    CACHE,  // Fill With Lock (I)
    CACHE,  // Index Write Back Invalidate (D)
    CACHE,  // Index Unlock (D)
    CACHE,  // Create Dirty Exclusive (D)
    CACHE,  // Hit Invalidate (D)
    CACHE,  // Hit Write Back (D)
    CACHE,  // Hit Write Back Invalidate (D)
    CACHE,  // Create Dirty Exclusive with Lock (D)
    CACHE,  // Fill (D)
    CACHE,  // Fill With Lock (D)
    CLO,    // Count Leading One
    CLZ,    // Count Leading Zero
    EXT,    // Extract Bit Field
    INS,    // Insert Bit Field
    LL,     // Load Linked
    MADD,   // Multiply Add
    MADDU,  // Multiply Add Usigned
    MAX,    // Select Max
    MIN,    // Select Min
    MOVN,   // 
    MOVZ,
    MSUB,
    MSUBU,
    ROTR,
    ROTRV,
    SC,
    SEB,
    SEH,
    SYNC,
    WSBH,
    WSBW
}

// map to lookup table OPCODE_TABLE[0,0] for fast access
// example const val :string = OPCODE_TABLE[0][0];
// how to access the opcode by parsing high and low bit on INSTRUCTION Table
// OPCODE_TABLE[high_idx][low_indx] on first 6 bit to decimal;
const OPCODE_TABLE : vec![vec![0; 7]; 7] = 
[
    ["SPECIAL","REGIMM","J","JAL","BEQ","BNE","BLEZ","BGTZ"],
    ["ADDI","ADDIU","SLTI","SLTIU","ANDI","ORI","XORI","LUI"],
    ["COP0","COP1","COP2","COP3","BEQL","BNEL","BLEZL","BGTZL"],
    ["VFPU0","VFPU1","*","VFPU3","SPECIAL2","*","*","SPECIAL3"],
    ["LB","LH","LWL","LW",]
];

