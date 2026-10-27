if (NOT CMAKE_ASM_COMPILER_LOADED)
    message(FATAL_ERROR "Enable assembly as part of your project's languages: project(my_project C CXX ASM)")
endif()

include(cmake/deploy-util.cmake)

# Libs --> EXCLUDE_FROM_ALL ensures mallow and exlaunch don't get compiled in INTERFACE build mode
add_subdirectory(libs/ArduinoJson EXCLUDE_FROM_ALL)
add_subdirectory(libs/exlaunch EXCLUDE_FROM_ALL)

# Custom
add_subdirectory(src/startup)
add_subdirectory(src/core-cpp)
add_subdirectory(src/core-smo)

set(ML_RUNTIME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/ml)
add_subdirectory(src/ml)

target_compile_definitions(ml_core_cpp PUBLIC NN_SWITCH) # To avoid compiling std stuff that only works on desktop
