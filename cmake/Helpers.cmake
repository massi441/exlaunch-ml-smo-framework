# The npdm describes the whole process, so only one npdm needs be created regardless of how many subsdk's there are
function(generate_npdm json)
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/main.npdm
        DEPENDS ${json}
        COMMAND ${CMAKE_SOURCE_DIR}/tools/npdmtool${EXE_EXT} ${json} ${CMAKE_BINARY_DIR}/main.npdm
    )
    add_custom_target(npdm DEPENDS ${CMAKE_BINARY_DIR}/main.npdm)
endfunction()

function(make_nso_target target subsdk_name)
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/${target}.nso
        DEPENDS ${target}
        COMMAND ${CMAKE_SOURCE_DIR}/tools/linkle nso $<TARGET_FILE:${target}> ${CMAKE_BINARY_DIR}/${target}.nso
    )
    add_custom_target(${target}_nso DEPENDS ${CMAKE_BINARY_DIR}/${target}.nso)
endfunction()

function(deploy_nso target subsdk_name name dest)
    if (NOT TARGET ${target}_nso)
        message(FATAL_ERROR "Target ${target} does not exist")
    endif()
    if (NOT MOD_NAME)
        message(FATAL_ERROR "MOD_NAME is not set, can't deploy ${target}")
    endif()
    if (NOT dest)
        message(FATAL_ERROR "No ${name} path set, can't deploy ${target}")
    endif()

    set(_exefs ${dest}/${MOD_NAME}/exefs)
    add_custom_command(
        OUTPUT ${_exefs}/${subsdk_name}
        DEPENDS ${CMAKE_BINARY_DIR}/${target}.nso
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${target}.nso ${_exefs}/${subsdk_name}
    )
    add_custom_target(${target}_${name}_deploy ALL DEPENDS ${_exefs}/${subsdk_name})
endfunction()
