# Find SystemC package
find_package(SystemCLanguage CONFIG REQUIRED PATHS ${SYSTEMC_HOME}/lib/cmake/SystemCLanguage NO_DEFAULT_PATH)

if(NOT SystemCLanguage_FOUND)
    message(FATAL_ERROR "SystemC package not found in ${SYSTEMC_HOME}/lib/cmake/SystemCLanguage")
    set(SYSTEMC_FOUND FALSE PARENT_SCOPE)
    return()
endif()

# Retrieve the C++ standard from SystemCLanguageConfig.cmake
if(DEFINED SystemC_CXX_STANDARD)
    set(SYSTEMC_CXX_STANDARD ${SystemC_CXX_STANDARD})
    message(STATUS "SystemC::systemc C++ standard: ${SYSTEMC_CXX_STANDARD}")
else()
    message(FATAL_ERROR "SystemC_CXX_STANDARD is not set in SystemCLanguageConfig.cmake")
    set(SYSTEMC_FOUND FALSE PARENT_SCOPE)
    return()
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
    set(SYSTEMC_FOUND FALSE PARENT_SCOPE)
    return()
elseif(SYSTEMC_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "SystemC::systemc requires at least C++17.")
    set(SYSTEMC_FOUND FALSE PARENT_SCOPE)
    return()
endif()

# Indicate that SystemC was found and configured correctly
set(SYSTEMC_FOUND TRUE)