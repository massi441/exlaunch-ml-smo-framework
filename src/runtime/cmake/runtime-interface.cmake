# Adds only the headers to the interface consumers link against
target_include_directories(ml_runtime INTERFACE ${ML_RUNTIME_DIR}/include)

target_link_libraries(ml_runtime INTERFACE
    $<COMPILE_ONLY:exlaunch>
    $<COMPILE_ONLY:marshmallow>
)
