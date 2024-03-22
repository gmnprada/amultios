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
    //  Flags Static Value Mips Instruction Header 000000  bits length
    #[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
    struct MipsInstructionOp: u32 {
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
        const J       = 0b000010;
        const JAL     = 0b000011;
        // NOT Possible on jump and links on 6 bits pattern
        const JALR    = 0b000000;
        const JR      = 0b000000;
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
    CACHE_INDEX_INVALIDATE,  // Index Invalidate (I)
    CACHE_INDEX_UNLOCK,  // Index Unlock (I)
    CACHE_HIT_INVALIDATE,  // Hit Invalidate (I)
    CACHE_FILL,  // Fill (I)
    CACHE_FILL_WITH_LOCK,  // Fill With Lock (I)
    CACHE_INDEX_WRITE_BACK,  // Index Write Back Invalidate (D)
    CACHE_INDEX_UNLOCK,  // Index Unlock (D)
    CACHE_CREATE_DIRTY_EXCLUSIVE,  // Create Dirty Exclusive (D)
    CACHE_HIT_INVALIDATE,  // Hit Invalidate (D)
    CACHE_HIT_WRITE_BACK,  // Hit Write Back (D)
    CACHE_HIT_WRITE_BACK_INVALIDATE,  // Hit Write Back Invalidate (D)
    CACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK,  // Create Dirty Exclusive with Lock (D)
    CACHE_FILL,  // Fill (D)
    CACHE_FILL_WITH_LOCK,  // Fill With Lock (D)
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
