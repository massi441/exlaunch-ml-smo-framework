add_subdirectory(startup)
add_subdirectory(core-cpp)
add_subdirectory(runtime)
add_subdirectory(core-smo)

target_compile_definitions(ml_core_cpp PUBLIC NN_SWITCH) # To avoid compiling std stuff that only works on desktop
