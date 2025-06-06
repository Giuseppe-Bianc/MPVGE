cmake_minimum_required(VERSION 3.21...3.28)  # Aggiornare alla versione minima di CMake necessaria

if (${CMAKE_VERSION} VERSION_LESS 3.21)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else ()
  cmake_policy(VERSION 3.28)
endif ()

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif ()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)


# Set the project name and language
project(
  MPVGE
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/Giuseppe-Bianc/MPVGE"
  LANGUAGES CXX C)

include(cmake/PreventInSourceBuilds.cmake)
include(ProjectOptions.cmake)


MPVGE_setup_options()

MPVGE_global_options()
include(Dependencies.cmake)
MPVGE_setup_dependencies()

MPVGE_local_options()

# don't know if this should be set globally from here or not...
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Extract the current Git SHA
find_package(Git REQUIRED)
execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_SHA
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the short version of the Git SHA
string(SUBSTRING "${GIT_SHA}" 0 8 GIT_SHORT_SHA)

# Define the Git SHA variables as cache variables
set(GIT_SHA "${GIT_SHA}" CACHE STRING "SHA this build was generated from")
set(GIT_SHORT_SHA "${GIT_SHORT_SHA}" CACHE STRING "Short SHA this build was generated from")


target_compile_features(MPVGE_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

add_library(MPVGE::MPVGE_options ALIAS MPVGE_options)
add_library(MPVGE::MPVGE_warnings ALIAS MPVGE_warnings)

#add_library(MPVGE::MPVGE_options INTERFACE IMPORTED)
#add_library(MPVGE::MPVGE_warnings INTERFACE IMPORTED)

# configure files based on CMake configuration options
add_subdirectory(configured_files)

# Adding the src:
add_subdirectory(src)

# Don't even look at tests if we're not top level
if (NOT PROJECT_IS_TOP_LEVEL)
  return()
endif ()

# Adding the tests:
include(CTest)

if (BUILD_TESTING)
  #  message(AUTHOR_WARNING "Building Tests. Be sure to check out test/constexpr_tests.cpp for constexpr testing")
  add_subdirectory(test)
endif ()


if(MPVGE_BUILD_FUZZ_TESTS)
  message(AUTHOR_WARNING "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  if (NOT MPVGE_ENABLE_ADDRESS_SANITIZER AND NOT MPVGE_ENABLE_THREAD_SANITIZER)
    message(WARNING "You need asan or tsan enabled for meaningful fuzz testing")
  endif ()
  add_subdirectory(fuzz_test)

endif ()

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
# so that it behaves well with MSVC's debugger, and we can run the target from visual studio
if (MSVC)
  get_all_installable_targets(all_targets)
  message("all_targets=${all_targets}")
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif ()

# set the startup project for the "play" button in MSVC
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT mvpge)

if (CMAKE_SKIP_INSTALL_RULES)
  return()
endif ()

include(cmake/PackageProject.cmake)

# Add other targets that you want installed here, by default we just package the one executable
# we know we want to ship
MPVGE_package_project(
  TARGETS
  mpvge
  MPVGE_options
  MPVGE_warnings
  # FIXME: this does not work! CK
  # PRIVATE_DEPENDENCIES_CONFIGURED project_options project_warnings
)

# Experience shows that explicit package naming can help make it easier to sort
# out potential ABI related issues before they start, while helping you
# track a build to a specific GIT SHA
set(CPACK_PACKAGE_FILE_NAME
        "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)

include(CPack)
