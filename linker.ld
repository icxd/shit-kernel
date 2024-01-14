/* entry point of the kernel */
ENTRY(start)

SECTIONS {
    . = 1M; /* some padding i guess? */

    /* text section */
    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }

    /* read only (RO) data section */
    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }

    /* data section */
    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

    /* bss section */
    .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMON)
        *(.bss)
    }


    end = .;
}
