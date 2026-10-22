# Interface that contains default configuration for any subsdk
add_library(subsdk_setup INTERFACE)

target_link_libraries(subsdk_setup INTERFACE
    -T ${CMAKE_SOURCE_DIR}/cmake/linker.ld
    -Wl,--no-whole-archive
    -Wl,--gc-sections
    -Wl,--hash-style=sysv
    -Wl,--build-id=uuid
    -Wl,-Bsymbolic # Linker resolves symbols for current module
    -Wl,-init,rtldInit
)

# rtld initializes subsdk's starting from the subsdk at the highest slot.
# The maximum slot is 9, so we reserve it to the runtime to ensure that it is initialized
# before any other subsdk that might depend on it
add_executable(subsdk9)

target_link_libraries(subsdk9 PRIVATE subsdk_setup)
target_compile_definitions(subsdk9 PRIVATE SUBSDK_MODULE_NAME="ml_runtime")

# These source files should be compiled per subsdk
set(STARTUP_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/startup/module.cpp
    ${CMAKE_SOURCE_DIR}/src/startup/init.cpp
    ${CMAKE_SOURCE_DIR}/src/startup/crt0.s
)

target_sources(subsdk9 PRIVATE ${STARTUP_SOURCE_FILES})

generate_npdm(${CMAKE_SOURCE_DIR}/src/npdm.json)
