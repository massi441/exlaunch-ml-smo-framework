if (NOT ML_OUTPUT_DIR)
    message(FATAL_ERROR "Ensure that the variable 'ML_OUTPUT_DIR' is specified")
endif()

if (NOT ML_TOOLS_DIR)
    message(FATAL_ERROR "Ensure that the variable 'ML_TOOLS_DIR' is specified")
endif()

file(MAKE_DIRECTORY ${ML_OUTPUT_DIR})

# A custom target that waits on generate_npdm and all subsdk's registered by make_subsdk
# ensures that deployments triggered by deploy_mod (see below) wait on all targets to be built into the output folder
add_custom_target(ml_deploy_deps)

# Creates a program description for a mod's exefs folder. Should be called at most once per build
# The npdm describes the whole process, so only one npdm needs be created regardless of how many subsdk's there are
# This function uses the provided the npdm.json file to the npdm tools and outputs it to the build directory
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
# and converts the target's ELF file into an NSO inside the output directory.
# You pass it the name of your CMake target, the name of the subsdk, and the name of your NSO module.
# example usage: make_subsdk(ml_runtime_subsdk "subsdk9" "ml_runtime")
function(make_subsdk target subsdk_name module_name)
    target_link_libraries(${target} PRIVATE ml_subsdk_common)
    target_link_libraries(${target} PRIVATE ml_subsdk_startup)
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

# Deploys the output folder into the specified destination folder.
# If you are deploying to a mod folder, ensure that the destination ends with '/exefs'
# example usage: deploy_mod("yuzu_deployment" "yuzu/MyModPath/exefs")
function(deploy_mod deployment_name dest)
    add_custom_target(${deployment_name} ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${ML_OUTPUT_DIR} ${dest}
    )
    add_dependencies(${deployment_name} ml_deploy_deps)
endfunction()

# TCP Deployment helper
