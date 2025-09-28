cmake_minimum_required(VERSION 3.10)

project(db-wrapper
		VERSION 0.0.1
		DESCRIPTION "database wrapper"
		LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
message(STATUS "CXX language require 20")

# set result output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# auto gen tables header file
set(DEFAULT_CMAKE_CONFIG_DIR ${CMAKE_SOURCE_DIR}/cmake)
include(${DEFAULT_CMAKE_CONFIG_DIR}/table-header.cmake)

set(CONFIG_FILE ${DEFAULT_CMAKE_CONFIG_DIR}/table-config/def.in)
set(TABLE_HEADER_GEN_DIR ${CMAKE_BINARY_DIR}/include/tables)
add_table_headers(${CONFIG_FILE} ${TABLE_HEADER_GEN_DIR})

# set compile_commands.json output
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set default header file include directory
set(DEFAULT_INCLUDE_DIR
		${CMAKE_SOURCE_DIR}/include
		${CMAKE_BINARY_DIR}/include/tables
)

add_subdirectory(lib)
