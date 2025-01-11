// test_sc_int_uint.cpp
#include <systemc.h>

int sc_main(int argc, char* argv[]) {
    // Declare sc_uint and sc_int variables
    sc_uint<8> u8; // 8-bit unsigned integer
    sc_int<8> i8;  // 8-bit signed integer

    // Assign values
    u8 = 255;
    i8 = -128;

    // Print initial values
    std::cout << "Initial values:" << std::endl;
    std::cout << "u8 = " << u8 << std::endl;
    std::cout << "i8 = " << i8 << std::endl;

    // Perform some operations
    u8 += 1;
    i8 -= 1;

    // Print values after operations
    std::cout << "Values after operations:" << std::endl;
    std::cout << "u8 = " << u8 << " (overflow expected)" << std::endl;
    std::cout << "i8 = " << i8 << std::endl;

    // Assign out-of-range values
    u8 = 300;
    i8 = 200;

    // Print values after assigning out-of-range values
    std::cout << "Values after assigning out-of-range values:" << std::endl;
    std::cout << "u8 = " << u8 << std::endl;
    std::cout << "i8 = " << i8 << std::endl;

    return 0;
}