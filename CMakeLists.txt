# Interface that contains default configuration for any subsdk
add_library(ml_subsdk_common INTERFACE)

target_link_libraries(ml_subsdk_common INTERFACE
    -T ${CMAKE_CURRENT_SOURCE_DIR}/cmake/linker.ld
    -Wl,--no-whole-archive
    -Wl,--gc-sections
    -Wl,--hash-style=sysv
    -Wl,--build-id=uuid
    -Wl,-Bsymbolic # Linker resolves symbols for current module
    -Wl,-init,rtldInit
)

include(cmake/deploy-util.cmake)

# Libs
add_subdirectory(libs/exlaunch)
add_subdirectory(libs/ArduinoJson)
add_subdirectory(libs/marshmallow)

# Custom
add_subdirectory(src)
