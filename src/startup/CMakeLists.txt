# A small library containing startup code for any compiled subsdk
add_library(ml_subsdk_startup INTERFACE)

target_sources(ml_subsdk_startup INTERFACE
    crt0.s
    init.cpp
    module.cpp
)
