/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
*/

#![no_std]
#![no_main]
#![allow(dead_code)]

mod arch;

use crate::arch::{cpu, gdt, interrupts};

use core::panic::PanicInfo;

#[no_mangle]
extern "C" fn kernel_main() -> ! {
    gdt::init();

    unsafe {
        interrupts::disable();

        loop {
            cpu::halt();
        }
    }
}

#[panic_handler]
fn rust_panic(_panic_info: &PanicInfo) -> ! {
    unsafe {
        interrupts::disable();

        loop {
            cpu::halt();
        }
    }
}