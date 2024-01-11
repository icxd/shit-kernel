#include <LibIO/Ports.hpp>
#include <Serial.hpp>

int init_serial(int port) {
    port_byte_out(port + 1, 0x00); // Disable all interrupts
    port_byte_out(port + 3, 0x80); // Enable DLAB (set baud rate divisor)
    port_byte_out(port + 0, 0x0C); // Set divisor to 3 (lo byte) 38400 baud
    port_byte_out(port + 1, 0x00); //                  (hi byte)
    port_byte_out(port + 3, 0x03); // 8 bits, no parity, one stop bit
    port_byte_out(port + 2,
                  0xC7); // Enable FIFO, clear them, with 14-byte threshold
    port_byte_out(port + 4, 0x0B); // IRQs enabled, RTS/DSR set
    port_byte_out(port + 4, 0x1E); // Set in loopback mode, test the serial
    // chip
    port_byte_out(port + 0, 0xAE); // Test serial chip (send byte 0xAE and check
                                   // if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if (port_byte_in(port + 0) != 0xAE) {
        return 1;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    port_byte_out(port + 4, 0x0F);
    return 0;
}