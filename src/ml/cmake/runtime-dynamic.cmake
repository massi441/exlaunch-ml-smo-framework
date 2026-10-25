# Builds the runtime as an executable that can be dynamically linked to other subsdk's
add_executable(ml_runtime_dynamic)

target_include_directories(ml_runtime_dynamic PRIVATE ${ML_RUNTIME_DIR}/detail)
target_include_directories(ml_runtime_dynamic PRIVATE ${ML_RUNTIME_DIR}/include)

target_link_libraries(ml_runtime_dynamic PRIVATE ml_core_cpp)
target_compile_options(ml_runtime_dynamic PRIVATE -fvisibility=hidden)
target_compile_definitions(ml_runtime_dynamic PRIVATE ML_DYNAMIC_RUNTIME)

# We compile & link these libraries once here so they are available at runtime for other subsdk's
# Mallow and exlaunch need all their symbols exported to make sure other subsdk's can find them at runtime
target_link_libraries(ml_runtime_dynamic PRIVATE
    -Wl,--whole-archive
    exlaunch
    -Wl,--no-whole-archive
)

target_compile_definitions(exlaunch PUBLIC EXL_DEBUG)

file(GLOB_RECURSE RUNTIME_SOURCES
    ${ML_RUNTIME_DIR}/src/*.cpp
)

target_sources(ml_runtime_dynamic PRIVATE
    main.cpp
    ${RUNTIME_SOURCES}
)

# The runtime's NSO goes into the output directory, the consumes manually deploy it to their mod folder.
# Note: rtld initializes subsdk's starting from the subsdk at the highest slot.
# The maximum slot is 9, so we reserve it to the runtime's subsdk, to ensure that it is initialized
# before any subsdk that might depend on it
make_subsdk(ml_runtime_dynamic "subsdk9" "ml_runtime")
