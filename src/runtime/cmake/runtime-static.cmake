# Builds the runtime as a library that can be statically linked to another subsdk
# subsdk's linking against this static library are responsible for compiling the startup sources as part of their module
add_library(ml_runtime_static)

target_include_directories(ml_runtime_static PRIVATE ${ML_RUNTIME_DIR}/detail)
target_include_directories(ml_runtime_static PUBLIC ${ML_RUNTIME_DIR}/include)

target_link_libraries(ml_runtime_static PRIVATE ml_core_cpp)

# Compiles marshmallow and exlaunch locally. Unlike in multi-subsdk mode, marshmallow and exlaunch don't
# need all their symbols kept since we already know which ones are used by the mod at link time
target_link_libraries(ml_runtime_static PUBLIC
    marshmallow
    exlaunch
)

file(GLOB_RECURSE RUNTIME_SOURCES
    ${ML_RUNTIME_DIR}/src/*.cpp
)

target_sources(ml_runtime_static PRIVATE
    ${RUNTIME_SOURCES}
)
