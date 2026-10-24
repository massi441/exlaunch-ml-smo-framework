if (NOT ML_OUTPUT_DIR)
    message(FATAL_ERROR "Ensure that the variable 'ML_OUTPUT_DIR' is specified")
endif()

if (NOT ML_SUBSDK_NAME_PROPERTY)
    message(FATAL_ERROR "Ensure that the variable 'ML_SUBSDK_NAME_PROPERTY' is specified")
endif()

if (NOT ML_TOOLS_DIR)
    message(FATAL_ERROR "Ensure that the variable 'ML_TOOLS_DIR' is specified")
endif()

file(MAKE_DIRECTORY ${ML_OUTPUT_DIR})

# The npdm describes the whole process, so only one npdm needs be created regardless of how many subsdk's there are
# This function uses the provided the npdm.json file to the npdm tools and outputs it to the build directory
function(generate_npdm json_path)
    add_custom_command(
        OUTPUT ${ML_OUTPUT_DIR}/main.npdm
        DEPENDS ${json_path}
        COMMAND ${ML_TOOLS_DIR}/npdmtool${EXE_EXT} ${json_path} ${ML_OUTPUT_DIR}/main.npdm
    )
    add_custom_target(npdm ALL DEPENDS ${ML_OUTPUT_DIR}/main.npdm)
endfunction()

# Converts a target's ELF file into an NSO, inside the output directory.
# You pass it the name of the target and the name of the resulting subsdk.
# example usage: make_nso(my_target subsdk8)
function(make_nso target subsdk_name)
    set_property(TARGET ${target} PROPERTY ${ML_SUBSDK_NAME_PROPERTY} ${subsdk_name})
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${ML_TOOLS_DIR}/linkle nso $<TARGET_FILE:${target}> ${ML_OUTPUT_DIR}/${subsdk_name}.nso
    )
endfunction()

# Deploys an NSO from the deploy folder into the provided destination folder
# You pass it the target you built the NSO with make_nso, the name of the
# deployment, and the destination folder of the deployment.
# If you are deploying to a mod folder, ensure that the destination ends with '/exefs'
# example usage: deploy_nso(my_target "yuzu_deployment" "yuzu/{...}/MyMod/exefs")
function(deploy_nso target deployment_name dest)
    if (NOT TARGET ${target})
        message(FATAL_ERROR "Cannot deploy ${subsdk_name}, ${target} does not exist")
    endif()

    get_property(subsdk_name TARGET ${target} PROPERTY ${ML_SUBSDK_NAME_PROPERTY})
    if (NOT subsdk_name)
        message(FATAL_ERROR "Cannot deploy ${target}, the subsdk name property '${ML_SUBSDK_NAME_PROPERTY}' was not set. Ensure 'make_nso' was called on your target")
    endif()

    if (NOT dest)
        message(FATAL_ERROR "Cannot deploy ${subsdk_name}, the destination path was not provided")
    endif()

    # Note: CMAKE_COMMAND represents the path of the CMake executable on the machine
    add_custom_command(
        OUTPUT ${dest}/${subsdk_name}
        DEPENDS ${target}
        COMMAND ${CMAKE_COMMAND} -E copy ${ML_OUTPUT_DIR}/${subsdk_name}.nso ${dest}/${subsdk_name}
    )
    add_custom_target(${deployment_name} ALL DEPENDS ${dest}/${subsdk_name})
endfunction()

# TCP Deployment helper
