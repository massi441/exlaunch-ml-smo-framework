add_library(ml_runtime INTERFACE)

# Adds only the headers to the interface consumers link against
target_include_directories(ml_runtime INTERFACE ${ML_RUNTIME_DIR}/include)

target_link_libraries(ml_runtime INTERFACE
    $<COMPILE_ONLY:exlaunch>
)

# TODO: Add docs for each value
option(ML_RUNTIME_BUILD_MODE "Specify the build mode of the runtime." OFF)

if (ML_RUNTIME_BUILD_MODE STREQUAL "STATIC")
    include(cmake/runtime-static.cmake)
elseif(ML_RUNTIME_BUILD_MODE STREQUAL "DYNAMIC")
    include(cmake/runtime-dynamic.cmake)
    target_include_directories(ml_runtime INTERFACE ${ML_RUNTIME_DIR}/include) # Headers for ml_runtime consumers
elseif (ML_RUNTIME_BUILD_MODE STREQUAL "INTERFACE")
    include(cmake/runtime-interface.cmake)
else()
    message(FATAL_ERROR "'ML_RUNTIME_BUILD_MODE' must be one of the following values: 'STATIC', 'DYNAMIC', 'INTERFACE'.")
endif()
