# Library holding all the registered mods
add_library(ml_mod_registry INTERFACE)

# Adds a registrable mod to the mod registry. Calling this function does
# not automatically mean the mod will be built and registered.
# This will depend on whether the build_option and register_option passed
# to this function are turned on in your build profile
function(ml_add_registerable_mod target dir build_option register_option)
    option(${build_option} "Enable building the ${dir} mod" OFF)

    # if building is undefined, then register should be rejected by default
    if (NOT ${build_option} AND NOT ${register_option})
        return()
    endif()

    add_subdirectory(${dir})

    target_link_libraries(ml_mod_registry INTERFACE ${target})
    target_compile_definitions(ml_mod_registry INTERFACE ${build_option})

    option(${register_option} "Enable registering the ${dir} mod" ON)
    if (${register_option})
        target_compile_definitions(ml_mod_registry INTERFACE ${register_option})
    endif()
endfunction()
