include(GenerateExportHeader)


add_library(mpvge_lib_core mpvge_lib_core.cpp)



add_library(MPVGE::mpvge_lib_core ALIAS mpvge_lib_core)

target_link_libraries(mpvge_lib_core PRIVATE MPVGE_options MPVGE_warnings)

target_include_directories(mpvge_lib_core ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(mpvge_lib_core PUBLIC cxx_std_20)

set_target_properties(
  mpvge_lib_core
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(mpvge_lib_core EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/MPVGE/mpvge_lib_core_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(mpvge_lib_core PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
endif()
