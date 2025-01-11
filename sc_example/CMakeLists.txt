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

# Retrieve the C++ standard from SystemCLanguageConfig.cmake
if(DEFINED SystemC_CXX_STANDARD)
    set(SYSTEMC_CXX_STANDARD ${SystemC_CXX_STANDARD})
    message(STATUS "SystemC::systemc C++ standard: ${SYSTEMC_CXX_STANDARD}")
else()
    message(FATAL_ERROR "SystemC_CXX_STANDARD is not set in SystemCLanguageConfig.cmake")
endif()

# Print the library files
message(STATUS "SystemC library files:")
get_target_property(SYSTEMC_LIB SystemC::systemc LOCATION)
message(STATUS "SystemC::systemc: ${SYSTEMC_LIB}")

# Dump properties of SystemC::systemc
get_target_property(SYSTEMC_INCLUDE_DIRS SystemC::systemc INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "SystemC::systemc include directories: ${SYSTEMC_INCLUDE_DIRS}")

get_target_property(SYSTEMC_LINK_LIBRARIES SystemC::systemc INTERFACE_LINK_LIBRARIES)
message(STATUS "SystemC::systemc link libraries: ${SYSTEMC_LINK_LIBRARIES}")

get_target_property(SYSTEMC_COMPILE_OPTIONS SystemC::systemc INTERFACE_COMPILE_OPTIONS)
message(STATUS "SystemC::systemc compile options: ${SYSTEMC_COMPILE_OPTIONS}")

# Verify the C++ standard
if(NOT SYSTEMC_CXX_STANDARD)
    message(FATAL_ERROR "SystemC::systemc C++ standard is not set.")
elseif(SYSTEMC_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "SystemC::systemc requires at least C++17.")
endif()

# Include SystemC headers
include_directories(${SYSTEMC_INCLUDE_DIRS})

# Add executable
add_executable(TestSCIntUint test_sc_int_uint.cpp)

# Set the C++ standard to the one used by SystemC
set_target_properties(TestSCIntUint PROPERTIES CXX_STANDARD ${SYSTEMC_CXX_STANDARD} CXX_STANDARD_REQUIRED YES)

# Link SystemC library
target_link_libraries(TestSCIntUint SystemC::systemc)