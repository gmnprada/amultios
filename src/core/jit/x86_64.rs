use dynasmrt::{DynasmApi, x64::Assembler};

fn add(assembler: &mut Assembler, rd: u8, rs: u8, rt: u8) {
    // Generate x86 assembly code for add rd, rs, rt
    assembler.mov(rax, rcx); // Move rcx (MIPS register $t0) to rax (x86 register)
    assembler.add(rax, rdx); // Add rdx (MIPS register $t1) to rax
    assembler.mov(qword_ptr(rbx, 8 * rd as i32), rax); // Move rax to rbx (MIPS memory) + 8 * rd
}

fn addi(assembler:&mut Assembler,){
    
}

fn translater_allegrex(assembler: &mut Assembler, instruction: MipsInstruction) {
    match instruction {
        MipsInstruction::Add(rd, rs, rt) => translate_add(assembler, rd, rs, rt),
    }
}