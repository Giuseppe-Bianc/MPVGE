include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(MPVGE_supports_sanitizers)
  if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else ()
    set(SUPPORTS_UBSAN OFF)
  endif ()

  if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else ()
    set(SUPPORTS_ASAN ON)
  endif ()
endmacro()

macro(MPVGE_setup_options)
  option(MPVGE_ENABLE_HARDENING "Enable hardening" ON)
  option(MPVGE_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    MPVGE_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    MPVGE_ENABLE_HARDENING
    OFF)

  MPVGE_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR MPVGE_PACKAGING_MAINTAINER_MODE)
    option(MPVGE_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(MPVGE_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(MPVGE_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(MPVGE_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(MPVGE_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(MPVGE_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(MPVGE_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(MPVGE_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(MPVGE_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(MPVGE_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(MPVGE_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(MPVGE_ENABLE_PCH "Enable precompiled headers" OFF)
    option(MPVGE_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(MPVGE_ENABLE_IPO "Enable IPO/LTO" ON)
    option(MPVGE_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(MPVGE_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(MPVGE_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(MPVGE_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(MPVGE_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(MPVGE_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(MPVGE_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(MPVGE_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(MPVGE_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(MPVGE_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(MPVGE_ENABLE_PCH "Enable precompiled headers" OFF)
    option(MPVGE_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if (NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      MPVGE_ENABLE_IPO
      MPVGE_WARNINGS_AS_ERRORS
      MPVGE_ENABLE_USER_LINKER
      MPVGE_ENABLE_SANITIZER_ADDRESS
      MPVGE_ENABLE_SANITIZER_LEAK
      MPVGE_ENABLE_SANITIZER_UNDEFINED
      MPVGE_ENABLE_SANITIZER_THREAD
      MPVGE_ENABLE_SANITIZER_MEMORY
      MPVGE_ENABLE_UNITY_BUILD
      MPVGE_ENABLE_CLANG_TIDY
      MPVGE_ENABLE_CPPCHECK
      MPVGE_ENABLE_COVERAGE
      MPVGE_ENABLE_PCH
      MPVGE_ENABLE_CACHE)
  endif()

  MPVGE_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (MPVGE_ENABLE_SANITIZER_ADDRESS OR MPVGE_ENABLE_SANITIZER_THREAD OR MPVGE_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else ()
    set(DEFAULT_FUZZER OFF)
  endif ()

  option(MPVGE_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(MPVGE_global_options)
  include(cmake/Simd.cmake)
  check_all_simd_features()
  print_simd_support()

  if(MPVGE_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    MPVGE_enable_ipo()
  endif()

  MPVGE_supports_sanitizers()

  if(MPVGE_ENABLE_HARDENING AND MPVGE_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR MPVGE_ENABLE_SANITIZER_UNDEFINED
       OR MPVGE_ENABLE_SANITIZER_ADDRESS
       OR MPVGE_ENABLE_SANITIZER_THREAD
       OR MPVGE_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else ()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${MPVGE_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${MPVGE_ENABLE_SANITIZER_UNDEFINED}")
    MPVGE_enable_hardening(MPVGE_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(MPVGE_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(MPVGE_warnings INTERFACE)
  add_library(MPVGE_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  MPVGE_set_project_warnings(
    MPVGE_warnings
    ${MPVGE_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(MPVGE_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    MPVGE_configure_linker(MPVGE_options)
  endif()

  include(cmake/Sanitizers.cmake)
  MPVGE_enable_sanitizers(
    MPVGE_options
    ${MPVGE_ENABLE_SANITIZER_ADDRESS}
    ${MPVGE_ENABLE_SANITIZER_LEAK}
    ${MPVGE_ENABLE_SANITIZER_UNDEFINED}
    ${MPVGE_ENABLE_SANITIZER_THREAD}
    ${MPVGE_ENABLE_SANITIZER_MEMORY})

  set_target_properties(MPVGE_options PROPERTIES UNITY_BUILD ${MPVGE_ENABLE_UNITY_BUILD})

  if(MPVGE_ENABLE_PCH)
    target_precompile_headers(
      MPVGE_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(MPVGE_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    MPVGE_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(MPVGE_ENABLE_CLANG_TIDY)
    MPVGE_enable_clang_tidy(MPVGE_options ${MPVGE_WARNINGS_AS_ERRORS})
  endif()

  if(MPVGE_ENABLE_CPPCHECK)
    MPVGE_enable_cppcheck(${MPVGE_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(MPVGE_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    MPVGE_enable_coverage(MPVGE_options)
  endif()

  if(MPVGE_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(MPVGE_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(MPVGE_ENABLE_HARDENING AND NOT MPVGE_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR MPVGE_ENABLE_SANITIZER_UNDEFINED
       OR MPVGE_ENABLE_SANITIZER_ADDRESS
       OR MPVGE_ENABLE_SANITIZER_THREAD
       OR MPVGE_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    MPVGE_enable_hardening(MPVGE_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
