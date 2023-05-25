const PSP_MEMORY_SIZE_32: usize = 32 * 1024 * 1024;
const PSP_MEMORY_SIZE_64: usize = 64 * 1024 * 1024;
struct PspMemory {
    memory: Vec<u8>,
}

impl PspMemory {
    fn new(psp_model:string) -> PspMemory {
        PspMemory {
            memory: vec![0; PSP_MEMORY_SIZE],
        }
    }

    fn read_u8(&self, address: usize) -> u8 {
        self.memory[address]
    }

    fn write_u8(&mut self, address: usize, value: u8) {
        self.memory[address] = value;
    }

    fn read_u32(&self, address: usize) -> u32 {
        u32::from_le_bytes([
            self.memory[address],
            self.memory[address + 1],
            self.memory[address + 2],
            self.memory[address + 3],
        ])
    }

    fn write_u32(&mut self, address: usize, value: u32) {
        let bytes = value.to_le_bytes();
        self.memory[address] = bytes[0];
        self.memory[address + 1] = bytes[1];
        self.memory[address + 2] = bytes[2];
        self.memory[address + 3] = bytes[3];
    }
}