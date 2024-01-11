#!/bin/bash

set -e

CC="g++"
CFLAGS="-m32 -std=c++20 -ffreestanding -O2 -Wall -Wextra -Iinclude -nostdlib -fno-pie"

USAGE="Usage: $(basename "$0") [OPTIONS]

Options:
    -h, --help     Displays this message
    -r, --run      Run the operating system
"

POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
    case $1 in
    -r | --run)
        RUN=true
        shift
        ;;
    -h | --help)
        echo "$USAGE"
        exit 0
        ;;
    -* | --*)
        echo "unknown option $1"
        exit 1
        ;;
    *)
        POSITIONAL_ARGS+=("$1")
        shift
        ;;
    esac
done
set -- "${POSITIONAL_ARGS[@]}" # restore positional args

mkdir -p build/arch/x86_64

as --32 arch/x86_64/boot.s -o build/arch/x86_64/boot.o

FILES=$(find src -name "*.cpp")
for FILE in $FILES; do
    echo "Compiling $FILE"
    $CC -c $FILE -o build/$(basename "${FILE%.*}").o $CFLAGS
done

OBJ_FILES=$(find build -name "*.o")

ld -m elf_i386 -T linker.ld \
    $OBJ_FILES \
    -o kernel.bin -nostdlib -z noexecstack
grub-file --is-x86-multiboot kernel.bin

mkdir -p iso/boot/grub
cp kernel.bin iso/boot/kernel.bin
cp grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o kernel.bin iso

if [[ "$RUN" = true ]]; then
    qemu-system-x86_64 \
        -cdrom kernel.bin \
        -no-reboot \
        -no-shutdown \
        -d int \
        -D qemu.log \
        -serial stdio
fi
