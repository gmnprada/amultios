
// simulate virtual PSP CPU Register on software emulation LLE ways
struct CpuGpr {
    zero : u32,  /* Wired Zero      $0 */      
    at   : u32,  /* Assembler Temp  $1 */
    v0   : u32,  /* Return Value    $2 */
    v1   : u32,  /*                 $3 */
    
    // Start Of Argument Register
    a0   : u32,
    a1   : u32,
    a2   : u32,
    a3   : u32,

    // this can be subtitutes use between eabi effective or not
    t0   : u32,
    t1   : u32,
    t2   : u32,
    t3   : u32,
    t4   : u32,
    t5   : u32,
    t6   : u32,
    t7   : u32,

    s0   : u32,
    s1   : u32,
    s2   : u32,
    s3   : u32,
    s4   : u32,
    s5   : u32,
    s6   : u32,
    s7   : u32,
    t8   : u32,
    t9   : u32,
    k0   : u32,
    k1   : u32,
    gp   : u32,
    sp   : u32,
    fp   : u32,
    ra   : u32
}