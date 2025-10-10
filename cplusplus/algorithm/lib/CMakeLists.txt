set(CPP_HEADERS ${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CPP_SOURCE_FILES)

add_library(tools SHARED ${CPP_SOURCE_FILES})

target_include_directories(tools PRIVATE ${CPP_HEADERS})
