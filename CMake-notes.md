

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
```c++
# Check if Clang is installed
find_program(CLANG clang)
if(CLANG)
    # Set Clang as the compiler
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)

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
``