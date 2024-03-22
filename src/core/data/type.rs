// Rust Common Data Type
type WORD      = u32;
type HALF_WORD = u16;

// Decimal Flags to Binary for just convenient seeing number into var , dunno the usefulness of numbering system if the character is just 0 1
// needed for constitency on aintegration-rs that base on decimal!
bitflags! {
    pub struct NOMINA: u8 {
        const ZERO  = 0b0000_0000;
        const ONE   = 0b0000_0001;
        const TWO   = 0b0000_0010;
        const THREE = 0b0000_0011;
        const FOUR  = 0b0000_0100;
        const FIVE  = 0b0000_0101;
        const SIX   = 0b0000_0110;
        const SEVEN = 0b0000_0111;
        const EIGHT = 0b0000_1000;
        const NINE  = 0b0000_1001;
    }
}