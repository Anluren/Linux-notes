#include <systemc.h>
#include <iostream>

// Define a structure with sc_int and sc_uint members
struct MyStruct {
    sc_uint<8> u8;  // 8-bit unsigned integer
    sc_int<8> i8;   // 8-bit signed integer
    sc_uint<64> u64; // 64-bit unsigned integer
    sc_int<64> i64;  // 64-bit signed integer

    // Constructor to initialize the members
    MyStruct() : u8(0), i8(0), u64(0), i64(0) {}

    // Method to print the values
    void print() const {
        std::cout << "u8 = " << u8 << ", i8 = " << i8 << ", u64 = " << u64 << ", i64 = " << i64 << std::endl;
    }
};

// Define a SystemC module that uses the structure
SC_MODULE(MyModule) {
    MyStruct my_struct;

    SC_CTOR(MyModule) {
        // Initialize the structure members
        my_struct.u8 = 255;
        my_struct.i8 = -128;
        my_struct.u64 = 1234567890123456789ULL;
        my_struct.i64 = -1234567890123456789LL;

        // Print the initial values
        SC_THREAD(print_values);
    }

    void print_values() {
        my_struct.print();
    }
};

int sc_main(int argc, char* argv[]) {
    MyModule my_module("my_module");
    sc_start();
    return 0;
}