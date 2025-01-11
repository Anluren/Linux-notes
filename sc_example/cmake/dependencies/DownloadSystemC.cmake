include(ExternalProject)

# Define the installation directory for SystemC
set(SYSTEMC_INSTALL_DIR ${CMAKE_BINARY_DIR}/systemc)

# Download and install SystemC from GitHub using CMake
ExternalProject_Add(
    systemc
    GIT_REPOSITORY https://github.com/accellera-official/systemc.git
    GIT_TAG master  # You can specify a specific tag, branch, or commit here
    PREFIX ${SYSTEMC_INSTALL_DIR}
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${SYSTEMC_INSTALL_DIR}
        -DCMAKE_CXX_STANDARD=17  # Specify the C++ standard
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR>
    INSTALL_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --target install
    UPDATE_DISCONNECTED 1  # Disable automatic updates
)

# Set SYSTEMC_HOME to the installation directory
set(SYSTEMC_HOME ${SYSTEMC_INSTALL_DIR} CACHE PATH "Path to the SystemC installation")