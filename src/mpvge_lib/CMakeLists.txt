include(GenerateExportHeader)


add_library(mpvge_lib mpvge_lib.cpp)



add_library(MPVGE::mpvge_lib ALIAS mpvge_lib)

target_link_libraries(mpvge_lib PRIVATE MPVGE_options MPVGE_warnings)

target_include_directories(mpvge_lib ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(mpvge_lib PUBLIC cxx_std_20)

set_target_properties(
  mpvge_lib
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(mpvge_lib EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/MPVGE/mpvge_lib_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(mpvge_lib PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
endif()
