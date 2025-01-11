// test_sc_int_uint.cpp
#include <systemc.h>
#include <iostream>

// Function to extend a bit at a given offset to all MSBs
template <typename T>
T extend_bit(T value, unsigned int offset) {
    // Calculate the mask to extend the bit
    T mask = static_cast<T>(-1) << offset;
    // Check if the bit at the given offset is set
    if (value & (1 << offset)) {
        // If set, extend the bit to all MSBs
        value |= mask;
    } else {
        // If not set, clear the MSBs
        value &= ~mask;
    }
    return value;
}

int sc_main(int argc, char* argv[]) {
    // Declare sc_uint and sc_int variables
    sc_uint<8> u8; // 8-bit unsigned integer
    sc_int<8> i8;  // 8-bit signed integer
    sc_uint<64> u64;
    // sc_uint<65> u65;

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

    // Extend bit at offset 3 for u8 and i8
    u8 = extend_bit(u8, 3);
    i8 = extend_bit(i8, 3);

    // Print values after bit extension
    std::cout << "Values after bit extension at offset 3:" << std::endl;
    std::cout << "u8 = " << u8 << std::endl;
    std::cout << "i8 = " << i8 << std::endl;

    // add code to check memory usage of sc_uint and sc_int
    std::cout << "Memory usage of sc_uint<8>: " << sizeof(u8) << " bytes" << std::endl;
    std::cout << "Memory usage of sc_int<8>: " << sizeof(i8) << " bytes" << std::endl;
    std::cout << "Memory usage of sc_uint<64>: " << sizeof(u64) << " bytes" << std::endl;
    // std::cout << "Memory usage of sc_uint<65>: " << sizeof(u65) << " bytes" << std::endl;

    // insert the result of the memory usage of sc_uint and sc_int
    // as comments in the code
    // Memory usage of sc_uint<8>: 24 bytes
    // Memory usage of sc_int<8>: 24 bytes
    // Memory usage of sc_uint<64>: 24 bytes


    // add more code to test sc_biguint and sc_bigint

    // Declare sc_biguint and sc_bigint variables
    sc_biguint<8> bu8; // 8-bit unsigned big integer
    sc_bigint<8> bi8;  // 8-bit signed big integer
    sc_biguint<64> bu64;
    sc_biguint<65> bu65;

    // assign values
    bu8 = 255;
    bi8 = -128;

    // assign value to bu65
    bu65 = 1234567890123456789ULL;

    // print initial values
    std::cout << "Initial values of sc_biguint and sc_bigint:" << std::endl;
    std::cout << "bu8 = " << bu8 << std::endl;
    std::cout << "bi8 = " << bi8 << std::endl;
    std::cout << "bu65 = " << bu65 << std::endl;


    return 0;
}