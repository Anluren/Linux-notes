

```cmake
#add subdirectory if it exists
set(SUBDIR ${CMAKE_SOURCE_DIR}/mysubdir)

if(EXISTS ${SUBDIR} AND IS_DIRECTORY ${SUBDIR})
    add_subdirectory(${SUBDIR})
else()
    message("The directory ${SUBDIR} does not exist!")
endif()
```

```cmake
# patch diff before build
# Define the patch file and the directory to apply it to
set(PATCH_FILE ${CMAKE_SOURCE_DIR}/patches/my_patch.patch)
set(TARGET_DIR ${CMAKE_SOURCE_DIR}/third_party/my_lib)

# Use execute_process to do a dry run of the patch command
execute_process(
    COMMAND patch --dry-run -p1 -i ${PATCH_FILE}
    WORKING_DIRECTORY ${TARGET_DIR}
    RESULT_VARIABLE patch_result
    OUTPUT_QUIET
    ERROR_QUIET
)

# If the dry run succeeded, the patch has not been applied yet
if(patch_result EQUAL 0)
    # Apply the patch
    execute_process(
        COMMAND patch -p1 -i ${PATCH_FILE}
        WORKING_DIRECTORY ${TARGET_DIR}
        RESULT_VARIABLE patch_result
    )

    # Check the result of the patch command
    if(NOT patch_result EQUAL 0)
        message(FATAL_ERROR "Failed to apply patch: ${PATCH_FILE}")
    endif()
endif()
```

```cmake
#check gcc version
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "11")
        message("GCC version is exactly 11!")
    else()
        message("GCC version is not 11!")
    endif()
endif()
```

use clang and libc++ if it's present
```cmake
# Check if Clang is installed
find_program(CLANG clang)
if(CLANG)
    # Get the directory of Clang and Clang++
    get_filename_component(CLANG_DIR ${CLANG} DIRECTORY)
    get_filename_component(CLANGXX_DIR ${CLANGXX} DIRECTORY)

    # Set the C and C++ compilers to Clang with full path
    set(CMAKE_C_COMPILER ${CLANG_DIR}/${CLANG})
    set(CMAKE_CXX_COMPILER ${CLANGXX_DIR}/${CLANGXX})

    # Check if LLVM's libc++ is installed
    include(CheckCXXSourceCompiles)
    set(CMAKE_REQUIRED_FLAGS "-stdlib=libc++")
    CHECK_CXX_SOURCE_COMPILES("
    #include <ciso646>
    int main() {
        return 0;
    }
    " LIBCXX_FOUND)

    if(LIBCXX_FOUND)
        # Set libc++ as the standard library
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    else()
        message(WARNING "LLVM's libc++ not found! Using default C++ standard library.")
    endif()
else()
    message(WARNING "Clang not found! Using default compiler.")
endif()
```

```cmake
# Check if target is ARM architecture
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    message("ARM architecture detected!")
endif()

# Check if target is x86 architecture
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86")
    message("x86 architecture detected!")
endif()

# Check if target is x86_64 architecture
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    message("x86_64 architecture detected!")
endif()

# check target is ARM or arm64
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    message("ARM or ARM64 architecture detected!")
endif()
```

```cmake
# in cross-compiling, check if target is ARM architecture

if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    message("ARM architecture detected!")
    set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
    set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
endif()
```

```c++
# Check if target is ARM architecture
#ifdef __arm__
    message("ARM architecture detected!")
#elif defined(__x86_64__) || defined(_M_X64)
    message("x86_64 architecture detected!")
#elif defined(__i386__) || defined(_M_IX86)
    message("x86 architecture detected!")
#else
    message("Unknown architecture detected!")
#endif
// Check if target is ARM32 architecture
#if defined(__arm__) && !defined(__aarch64__)
    message("ARM32 architecture detected!")
#endif

// Check if target is ARM64 architecture
#if defined(__aarch64__)
    message("ARM64 architecture detected!")
#endif
```

```cmake
if(CMAKE_CXX_FLAGS MATCHES "-m32" OR CMAKE_C_FLAGS MATCHES "-m32")
    message("The -m32 option is set.")
else()
    message("The -m32 option is not set.")
endif()
```

```cmake
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    message("Clang compiler is being used.")
    if(CMAKE_CXX_FLAGS MATCHES "-m32" OR CMAKE_C_FLAGS MATCHES "-m32")
        message("The -m32 option is set.")
    else()
        message("The -m32 option is not set.")
    endif()
else()
    message("Clang compiler is not being used.")
endif()
```

```cmake
execute_process(COMMAND cmd ARGS arg1 arg2
                RESULT_VARIABLE cmd_result
                OUTPUT_VARIABLE cmd_output)

if(NOT ${cmd_result} EQUAL 0)
    message(WARNING "Command failed with error: ${cmd_result}")
    message(WARNING "Output: ${cmd_output}")
else()
    message("Command succeeded with output: ${cmd_output}")
endif()
```

#choose Nina if it's installed
```bash
#!/bin/bash

# Try to find Ninja
ninja_path=$(which ninja)

if [[ -n "$ninja_path" ]]; then
    cmake -G Ninja ..
else
    cmake -G "Unix Makefiles" ..
fi
```

```cmake
# for cmake version since 3.29
# Attempt to find lld by checking its version
execute_process(COMMAND lld --version
                RESULT_VARIABLE lld_result
                OUTPUT_VARIABLE lld_version_output
                ERROR_QUIET
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# Check if the command was successful (result variable is 0)
if(lld_result EQUAL 0)
    message(STATUS "LLD linker found: ${lld_version_output}")

    # Explicitly set lld as the linker
    set(CMAKE_LINKER "lld" CACHE FILEPATH "LLD linker" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld" CACHE STRING "Use LLD linker" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=lld" CACHE STRING "Use LLD linker" FORCE)
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fuse-ld=lld" CACHE STRING "Use LLD linker" FORCE)
else()
    message(STATUS "LLD linker not found. Using default system linker.")
endif()
```

```
# for cmake version prior to 3.29
# Attempt to find lld by checking its version
execute_process(COMMAND lld --version
                RESULT_VARIABLE lld_result
                OUTPUT_VARIABLE lld_version_output
                ERROR_QUIET
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# Check if the command was successful (result variable is 0)
if(lld_result EQUAL 0)
    message(STATUS "LLD linker found: ${lld_version_output}")

    # For older CMake versions, set linker flags for C and C++ directly
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fuse-ld=lld" CACHE STRING "Use LLD linker for C" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=lld" CACHE STRING "Use LLD linker for C++" FORCE)
else()
    message(STATUS "LLD linker not found. Using default system linker.")
endif()
#[[
CMake's FetchContent module does not directly support switching between HTTPS and SSH URLs if one of them isn't working. However, you can implement this functionality yourself by checking if the FetchContent_MakeAvailable command succeeds for one URL and, if not, trying again with the other URL.
]]

include(FetchContent)

set(MYLIB_HTTPS_URL https://github.com/username/mylib.git)
set(MYLIB_SSH_URL git@github.com:username/mylib.git)

FetchContent_Declare(
  mylib
  GIT_REPOSITORY ${MYLIB_HTTPS_URL}
  GIT_TAG        v1.0.0
)

# Try to fetch the content using the HTTPS URL
execute_process(
  COMMAND ${CMAKE_COMMAND} -E fetch_content mylib
  RESULT_VARIABLE result
)

# If the fetch failed, try again with the SSH URL
if(result)
  message("Failed to fetch content using HTTPS URL, trying with SSH URL...")
  FetchContent_Declare(
    mylib
    GIT_REPOSITORY ${MYLIB_SSH_URL}
    GIT_TAG        v1.0.0
  )
  FetchContent_MakeAvailable(mylib)
else()
  FetchContent_MakeAvailable(mylib)
endif()

```

```cmake
# ---------------------------------------------------------------------------------------
# External project configuration
# ---------------------------------------------------------------------------------------
include(ExternalProject)

ExternalProject_Add(
    external_project_name
    PREFIX ${CMAKE_BINARY_DIR}/external_project_name
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/path/to/external/project
    CONFIGURE_COMMAND ""  # Skip configure step if not needed
    BUILD_COMMAND cd ${CMAKE_SOURCE_DIR}/path/to/build/directory && make  # Change directory and run make
    INSTALL_COMMAND ""    # No install command
    BUILD_IN_SOURCE 1     # Build in the source directory
    BUILD_BYPRODUCTS 
        ${CMAKE_BINARY_DIR}/external_project_name/src/external_project_name-build/libexternal_project_name.so
        ${CMAKE_BINARY_DIR}/external_project_name/src/external_project_name-build/libexternal_project_name.dylib
        ${CMAKE_BINARY_DIR}/external_project_name/src/external_project_name-build/external_project_name.dll
)

# Manually specify include directories and library paths
include_directories(${CMAKE_SOURCE_DIR}/path/to/external/project/include)
link_directories(${CMAKE_BINARY_DIR}/external_project_name/src/external_project_name-build)

# Create an imported library target
add_library(external_project_name_lib SHARED IMPORTED)

# Set the IMPORTED_LOCATION property based on the platform
if (UNIX AND NOT APPLE)
    set_target_properties(external_project_name_lib PROPERTIES
        IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/external_project_name/src/external_project_name-build/libexternal_project_name.so
    )
elseif (APPLE)
    set_target_properties(external_project_name_lib PROPERTIES
        IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/external_project_name/src/external_project_name-build/libexternal_project_name.dylib
    )
elseif (WIN32)
    set_target_properties(external_project_name_lib PROPERTIES
        IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/external_project_name/src/external_project_name-build/external_project_name.dll
    )
endif()

# Link the imported library to your target
target_link_libraries(your_target_name external_project_name_lib)
```

cmake to generate header file from xml:
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the XML file and the script
set(XML_FILE ${CMAKE_SOURCE_DIR}/input.xml)
set(SCRIPT ${CMAKE_SOURCE_DIR}/generate_code.py)

# Define the output directory for generated files
set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

# Define the generated C++ files
set(GENERATED_CPP_FILES
    ${GENERATED_DIR}/generated_code1.cpp
    ${GENERATED_DIR}/generated_code2.cpp
    ${GENERATED_DIR}/generated_code3.cpp
)
set(GENERATED_H_FILES
    ${GENERATED_DIR}/generated_code1.h
    ${GENERATED_DIR}/generated_code2.h
    ${GENERATED_DIR}/generated_code3.h
)

# Add a custom command to run the script and generate the C++ files
add_custom_command(
    OUTPUT ${GENERATED_CPP_FILES} ${GENERATED_H_FILES}
    COMMAND ${CMAKE_COMMAND} -E env python ${SCRIPT} ${XML_FILE} ${GENERATED_DIR}
    DEPENDS ${XML_FILE} ${SCRIPT}
    COMMENT "Generating C++ code from XML"
    VERBATIM
)

# Add a custom target that depends on the generated files
add_custom_target(generate_code ALL DEPENDS ${GENERATED_CPP_FILES} ${GENERATED_H_FILES})

# Add the executable and link the generated files
add_executable(MyProject main.cpp ${GENERATED_CPP_FILES})
add_dependencies(MyProject generate_code)
include_directories(${GENERATED_DIR})
```

```
# how to build compilation database with make
# python compiledb : https://github.com/nickdiego/compiledb
compiledb -n make
```

