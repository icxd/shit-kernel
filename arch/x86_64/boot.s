.set MAGIC, 0x1BADB002 /* magic number */
.set FLAGS, 0 /* no flags yet */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum */

/* multiboot header */
.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

stack_bottom:
    .skip 1024
stack_top:

.section .text
.extern kmain
.global start
.type start, @function

start:
    mov $stack_top, %esp

    push %ebx
    push %eax
    call kmain

    cli

.loop:
    hlt
    jmp .loop

.size start, . - start
