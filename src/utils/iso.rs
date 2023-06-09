use std::fs::File;
use std::io::{Read, Result};

pub fn read_iso_file(filename: &str) -> Result<Vec<u8>> {
    let mut file = File::open(filename)?;
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer)?;
    Ok(buffer)
}