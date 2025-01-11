cmake_minimum_required(VERSION 3.10)
project(TestSCIntUint)

# Add the cmake directory to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Check if SYSTEMC_HOME is set as a CMake parameter or environment variable
if(NOT DEFINED SYSTEMC_HOME)
    if(DEFINED ENV{SYSTEMC_HOME})
        set(SYSTEMC_HOME $ENV{SYSTEMC_HOME})
    else()
        # Add the dependencies directory to handle downloading and installing SystemC
        add_subdirectory(dependencies)
    endif()
endif()

# Include the FindSystemC.cmake file
include(FindSystemC)

# Check if SystemC was found and configured correctly
if(NOT SYSTEMC_FOUND)
    message(WARNING "SystemC was not found or configured correctly. Skipping the build of TestSCIntUint target.")
    return()
endif()

# Add executable
add_executable(TestSCIntUint test_sc_int_uint.cpp)

# Set the C++ standard to the one used by SystemC
set_target_properties(TestSCIntUint PROPERTIES CXX_STANDARD ${SYSTEMC_CXX_STANDARD} CXX_STANDARD_REQUIRED YES)

# Link SystemC library
target_link_libraries(TestSCIntUint SystemC::systemc)

# add new target with test_sc_struct.cpp
add_executable(TestSCStruct test_sc_struct.cpp)

# Set the C++ standard to the one used by SystemC
set_target_properties(TestSCStruct PROPERTIES CXX_STANDARD ${SYSTEMC_CXX_STANDARD} CXX_STANDARD_REQUIRED YES)

# Link SystemC library
target_link_libraries(TestSCStruct SystemC::systemc)
