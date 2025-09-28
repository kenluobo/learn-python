add_executable(db-wrapper main.cpp)
target_include_directories(db-wrapper 
  PRIVATE
  ${DEFAULT_INCLUDE_DIR}
)
