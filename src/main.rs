#![no_std]  // Not Link The Std Lib for Free Stand OS Independent
#![no_main] // Sadly we didn't know what is privilege and how to write driver yet, ignore me captain!

// This is needed or just abort and crash the whole hardware on host isa and abi !
use core::panic::PanicInfo;

#[no_mangle]
pub extern "C" fn _boot() -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn _initial_pre_loader() -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn _kernel() -> ! {
    loop {}
}

// This Function Implement Unwinding behavior of rust
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}