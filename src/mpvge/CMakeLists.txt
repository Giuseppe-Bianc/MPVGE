add_executable(mpvge main.cpp)

target_link_libraries(
  mpvge
  PRIVATE MPVGE::MPVGE_options
          MPVGE::MPVGE_warnings)

target_link_system_libraries(
  mpvge
  PRIVATE
          CLI11::CLI11
          MPVGE::mpvge_lib)

target_include_directories(mpvge PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
