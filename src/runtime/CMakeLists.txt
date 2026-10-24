add_library(ml_runtime INTERFACE)

option(MULTI_SUBSDK "Build the runtime as a separate subsdk" OFF)
option(NO_RUNTIME_BUILD "Skip building the runtime, and only use its headers" OFF)

if (USE_RUNTIME_INTERFACE)
    set(MULTI_SUBSDK ON)
    include(runtime-interface.cmake)
else()


    if (MULTI_SUBSDK)
        include(runtime-dynamic.cmake)
    else()
        include(runtime-static.cmake)
    endif()
endif()