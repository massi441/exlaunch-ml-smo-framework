add_library(ml_runtime INTERFACE)

# TODO: Add docs for each value
option(ML_RUNTIME_BUILD_MODE "Specify the build mode of the runtime." OFF)

if (ML_RUNTIME_BUILD_MODE STREQUAL "STATIC")
    include(cmake/runtime-static.cmake)
    target_link_libraries(ml_runtime INTERFACE ml_runtime_static)
elseif(ML_RUNTIME_BUILD_MODE STREQUAL "DYNAMIC")
    include(cmake/runtime-dynamic.cmake)
elseif (ML_RUNTIME_BUILD_MODE STREQUAL "INTERFACE")
    include(cmake/runtime-interface.cmake)
else()
    message(FATAL_ERROR "'ML_RUNTIME_BUILD_MODE' must be one of the following values: 'STATIC', 'DYNAMIC', 'INTERFACE'.")
endif()
