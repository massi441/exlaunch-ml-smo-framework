if (NOT ML_OUTPUT_DIR)
    message(FATAL_ERROR "Ensure that the variable 'ML_OUTPUT_DIR' is specified")
endif()

if (NOT ML_TOOLS_DIR)
    message(FATAL_ERROR "Ensure that the variable 'ML_TOOLS_DIR' is specified")
endif()

file(MAKE_DIRECTORY ${ML_OUTPUT_DIR})

# If the user switches to static build mode, we need to ensure any stale runtime subsdk9 is deleted from the output folder
if (ML_RUNTIME_BUILD_MODE STREQUAL "STATIC")
    file(REMOVE ${ML_OUTPUT_DIR}/subsdk9)
endif()

# A custom target that waits on generate_npdm and all subsdk's registered by make_subsdk
# ensures that deployments triggered by deploy_mod (see below) wait on all targets to be built into the output folder
add_custom_target(ml_deploy_deps)

# An interface that contains default link options for any subsdk, and is used by make_subsdk below
add_library(ml_subsdk_link_options INTERFACE)

target_link_options(ml_subsdk_link_options INTERFACE
    -T ${CMAKE_CURRENT_SOURCE_DIR}/cmake/linker.ld
    -Wl,--no-whole-archive
    -Wl,--gc-sections
    -Wl,--hash-style=sysv
    -Wl,--build-id=uuid
    -Wl,-Bsymbolic # Linker resolves symbols for current module
    -Wl,-init,rtldInit
)

# Creates a program description for a mod's exefs folder
# The npdm describes the whole process, so only one npdm needs be created regardless
# of how many subsdk's are part of a mod
function(generate_npdm json_path)
    add_custom_command(
        OUTPUT ${ML_OUTPUT_DIR}/main.npdm
        DEPENDS ${json_path}
        COMMAND ${ML_TOOLS_DIR}/npdmtool${EXE_EXT} ${json_path} ${ML_OUTPUT_DIR}/main.npdm
    )
    add_custom_target(generate_npdm ALL DEPENDS ${ML_OUTPUT_DIR}/main.npdm)
    add_dependencies(ml_deploy_deps generate_npdm)
endfunction()

# Creates a standalone subsdk from a target: links common flags, the startup code,
# and converts the target's ELF file into an NSO inside the output directory
# You pass it the name of your CMake target, the name of the subsdk, and the name of your NSO module.
# example usage: make_subsdk(ml_runtime_dynamic "subsdk9" "ml_runtime")
function(make_subsdk target subsdk_name module_name)
    target_link_libraries(${target} PRIVATE
        ml_subsdk_startup
        ml_subsdk_link_options
    )

    target_compile_definitions(${target} PRIVATE ML_SUBSDK_MODULE_NAME="${module_name}")

    set(subsdk_output_path ${ML_OUTPUT_DIR}/${subsdk_name})

    add_custom_command(
        OUTPUT ${subsdk_output_path}
        DEPENDS ${target}
        COMMAND ${ML_TOOLS_DIR}/linkle nso $<TARGET_FILE:${target}> ${subsdk_output_path}
    )

    add_custom_target(${target}_nso ALL DEPENDS ${subsdk_output_path})
    add_dependencies(ml_deploy_deps ${target}_nso)
endfunction()

# Deploys the current output folder into the given destination folder.
# If you are deploying to a mod folder, ensure that the destination ends with '/exefs'
# example usage: deploy_mod(deploy_target "${yuzu_path}/MyModPath/exefs")
function(deploy_mod deployment_name dest)
    # Need to cleanup any stale runtime subsdk9 from previous builds
    if (ML_RUNTIME_BUILD_MODE STREQUAL "STATIC")
        add_custom_target(${deployment_name} ALL
            COMMAND ${CMAKE_COMMAND} -E rm -f ${dest}/subsdk9
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${ML_OUTPUT_DIR} ${dest}
        )
    else()
        add_custom_target(${deployment_name} ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${ML_OUTPUT_DIR} ${dest}
        )
    endif()
    add_dependencies(${deployment_name} ml_deploy_deps)
endfunction()

# TODO: TCP Deployment helper
