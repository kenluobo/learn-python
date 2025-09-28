function(add_table_headers CONFIG_FILE GEN_DIR)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)

    if(NOT GEN_DIR)
        message(FATAL_ERROR "GEN_DIR is empty")
    endif()

    file(MAKE_DIRECTORY ${GEN_DIR})

    if(NOT EXISTS "${CONFIG_FILE}")
        message(FATAL_ERROR "CONFIG_FILE does not exist: ${CONFIG_FILE}")
    endif()

    set(GEN_HEADER_PY ${CMAKE_SOURCE_DIR}/cmake/table-config/gen-table-header.py)

    add_custom_target(generate_headers ALL
        COMMAND ${Python3_EXECUTABLE} ${GEN_HEADER_PY}
                ${CONFIG_FILE} ${GEN_DIR}
        DEPENDS "${CONFIG_FILE}" "${GEN_HEADER_PY}"
        COMMENT "Generating all table headers"
    )
endfunction()

