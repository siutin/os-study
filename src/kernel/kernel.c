#include "kernel.h"

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif


void kernel_main() {

	// Initialise all the ISRs and segmentation
	init_descriptor_tables();

	/* Initialize terminal interface */
	terminal_initialize();

	/* Since there is no support for newlines in terminal_putchar
         * yet, '\n' will produce some VGA specific character instead.
         * This is normal.
         */

	terminal_writestring( "Hello, World!\n");
	asm volatile("int $0x3");
	asm volatile("int $0x4");
	asm volatile("int $0x12");

}
