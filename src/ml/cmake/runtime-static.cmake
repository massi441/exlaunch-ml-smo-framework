# Builds the runtime as a library that can be statically linked to another subsdk
# subsdk's linking against this static library are responsible for compiling the startup sources as part of their module
add_library(ml_runtime_static)

target_include_directories(ml_runtime_static PRIVATE ${ML_RUNTIME_DIR}/detail)
target_include_directories(ml_runtime_static PUBLIC ${ML_RUNTIME_DIR}/include)

target_link_libraries(ml_runtime_static PRIVATE ml_core_cpp)

# Compiles exlaunch locally. Unlike in multi-subsdk mode, exlaunch doesn'tm need all
# its symbols kept since we already know which ones are used by the mod at link time
target_link_libraries(ml_runtime_static PUBLIC
    exlaunch
)

file(GLOB_RECURSE RUNTIME_SOURCES
    ${ML_RUNTIME_DIR}/src/*.cpp
)

target_sources(ml_runtime_static PRIVATE
    ${RUNTIME_SOURCES}
)

# Allows consumers to manually initialize the runtime if they statically link it
target_compile_definitions(ml_runtime INTERFACE ML_STATIC_RUNTIME)

# Consumers that link against ml_runtime get the static library with them
target_link_libraries(ml_runtime INTERFACE ml_runtime_static)
