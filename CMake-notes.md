

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
