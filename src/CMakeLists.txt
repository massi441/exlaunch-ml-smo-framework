add_subdirectory(startup)
add_subdirectory(core-cpp)
add_subdirectory(core-smo)

set(ML_RUNTIME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/runtime)
add_subdirectory(runtime)

target_compile_definitions(ml_core_cpp PUBLIC NN_SWITCH) # To avoid compiling std stuff that only works on desktop
