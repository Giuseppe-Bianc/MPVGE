add_executable(mvpge main.cpp)

target_link_libraries(
  mvpge
  PRIVATE MPVGE::MPVGE_options
          MPVGE::MPVGE_warnings)

target_link_system_libraries(
  mvpge
  PRIVATE
          CLI11::CLI11
          MPVGE::mpvge_lib)

target_include_directories(mvpge PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
