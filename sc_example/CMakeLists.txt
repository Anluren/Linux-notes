cmake_minimum_required(VERSION 3.10)
project(TestSCIntUint)

# Check if SYSTEMC_HOME is set as a CMake parameter or environment variable
if(NOT DEFINED SYSTEMC_HOME)
    if(DEFINED ENV{SYSTEMC_HOME})
        set(SYSTEMC_HOME $ENV{SYSTEMC_HOME})
    else()
        message(FATAL_ERROR "SYSTEMC_HOME is not set. Please specify the SystemC installation path using -DSYSTEMC_HOME=/path/to/systemc or set the SYSTEMC_HOME environment variable.")
    endif()
endif()

# Find SystemC package
find_package(SystemCLanguage CONFIG REQUIRED PATHS ${SYSTEMC_HOME}/lib/cmake/SystemCLanguage NO_DEFAULT_PATH)

if(NOT SystemCLanguage_FOUND)
    message(FATAL_ERROR "SystemC package not found in ${SYSTEMC_HOME}/lib/cmake/SystemCLanguage")
endif()

# Print the library files
message(STATUS "SystemC library files:")
get_target_property(SYSTEMC_LIB SystemC::systemc LOCATION)
message(STATUS "SystemC::systemc: ${SYSTEMC_LIB}")

# Include SystemC headers
# include_directories(${SYSTEMC_HOME}/include)
# Add executable
add_executable(TestSCIntUint test_sc_int_uint.cpp)

# Set the C++ standard to C++17
set_target_properties(TestSCIntUint PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

# Link SystemC library
target_link_libraries(TestSCIntUint SystemC::systemc)