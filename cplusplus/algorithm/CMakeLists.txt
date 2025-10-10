cmake_minimum_required(VERSION 3.24.2 FATAL_ERROR)

project(
        DataStructure
        VERSION 0.1
        DESCRIPTION "learn data structure"
        LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/runtime)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

option(ENABLE_TEST "Enable test case" OFF)
if (ENABLE_TEST)
    message(STATUS "Enable test case")
    add_subdirectory(test)
endif ()

add_subdirectory(lib)
