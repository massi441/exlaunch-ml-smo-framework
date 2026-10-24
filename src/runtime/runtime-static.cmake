# Builds the runtime as a library that can be statically linked to another subsdk
# subsdk's linking against this static library are responsible for compiling the startup sources as part of their module
add_library(ml_runtime_static_lib)

target_include_directories(ml_runtime_static_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/detail)
target_include_directories(ml_runtime_static_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(ml_runtime_static_lib PRIVATE common_deps)
target_link_libraries(ml_runtime_static_lib PRIVATE ml_core_cpp)

# Compiles marshmallow and exlaunch locally. Unlike in multi-subsdk mode, marshmallow and exlaunch don't
# need all its symbols kept since we already know which ones are used by the mod ahead of time
target_link_libraries(ml_runtime_static_lib PUBLIC
    marshmallow
    exlaunch
)

target_compile_definitions(ml_runtime_static_lib PUBLIC SINGLE_SUBSDK)

file(GLOB_RECURSE RUNTIME_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

target_sources(ml_runtime_static_lib PRIVATE
    runtime.cpp # Need the runtime compiled so the mod preset can use it
    ${RUNTIME_SOURCES}
)

target_include_directories(ml_runtime_static_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
