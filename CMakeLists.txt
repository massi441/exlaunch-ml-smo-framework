include(cmake/Helpers.cmake)

# Interface that contains default configuration for any subsdk
add_library(subsdk_common INTERFACE)

target_link_libraries(subsdk_common INTERFACE
    -T ${CMAKE_CURRENT_SOURCE_DIR}/cmake/linker.ld
    -Wl,--no-whole-archive
    -Wl,--gc-sections
    -Wl,--hash-style=sysv
    -Wl,--build-id=uuid
    -Wl,-Bsymbolic # Linker resolves symbols for current module
    -Wl,-init,rtldInit
)

#target_link_libraries(subsdk_common INTERFACE ml_core_cpp)

set(RUNTIME_LIBS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# Libs
add_subdirectory(${RUNTIME_LIBS_PATH}/exlaunch)
add_subdirectory(${RUNTIME_LIBS_PATH}/ArduinoJson)
add_subdirectory(${RUNTIME_LIBS_PATH}/marshmallow)

# Custom
add_subdirectory(src)
