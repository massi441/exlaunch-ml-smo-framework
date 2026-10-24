# Builds the runtime as an executable that can be dynamically linked to other subsdk's
add_executable(ml_runtime_subsdk)

target_include_directories(ml_runtime_subsdk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/detail)
target_include_directories(ml_runtime_subsdk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(ml_runtime_subsdk PRIVATE ml_subsdk_common)
target_link_libraries(ml_runtime_subsdk PRIVATE ml_core_cpp)
target_link_libraries(ml_runtime_subsdk PRIVATE ml_subsdk_startup) # Module specific stuff (Since it's built as a separate subsdk)

# Compile & Link these libraries once here so they are available at runtime for other subsdk's
# Mallow and exlaunch need all their symbols exported to make sure other subsdk's can find them at runtime
target_link_libraries(ml_runtime_subsdk PRIVATE
    -Wl,--whole-archive
    marshmallow
    exlaunch
    -Wl,--no-whole-archive
)

target_compile_definitions(exlaunch PUBLIC EXL_DEBUG)

target_sources(ml_runtime_subsdk PRIVATE
    main.cpp
    runtime.cpp
    ${RUNTIME_SOURCES}
)

target_compile_definitions(ml_runtime_subsdk PRIVATE SUBSDK_MODULE_NAME="ml_runtime")

# The runtime's NSO goes into the output directory, the consumes manually deploy it to their mod folder.
# Note: rtld initializes subsdk's starting from the subsdk at the highest slot.
# The maximum slot is 9, so we reserve it to the runtime's subsdk, to ensure that it is initialized
# before any subsdk that might depend on it
make_nso(ml_runtime_subsdk "subsdk9")
