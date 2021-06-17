cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0079 NEW)

SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "7")
SET(CPACK_PACKAGE_VERSION_PATCH "2")
SET(COMPLETE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
project(GisL LANGUAGES CXX VERSION ${COMPLETE_VERSION})

set(QT_VERSION_MAJOR 5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

####################################################
# set path to additional CMake modules
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

####################################################
# get the current working branch
execute_process(
        COMMAND git describe --all --dirty
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE GISL_GIT_DESCRIPTION
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

####################################################
# last commit hash
execute_process(
        COMMAND git log -1 --format=%H
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE GISL_GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(TIMESTAMP TNTN_TIMESTAMP "%Y%m%dT%H%MZ" UTC)

####################################################
# Doxygen
message(STATUS "Build documentation open")
include(${CMAKE_SOURCE_DIR}/cmake/build_doxygen.cmake)
build_doxygen()

####################################################
# Sphinx
include(${CMAKE_SOURCE_DIR}/cmake/FindSphinx.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/UseSphinxDoc.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/UseBreathe.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/mySphinxConfig.cmake)

####################################################
# Qt
#include(${CMAKE_SOURCE_DIR}/cmake/myQtConfig.cmake)
#find_package(QT NAMES Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Gui LinguistTools REQUIRED)
find_package(Qt5 COMPONENTS Widgets Gui LinguistTools REQUIRED)

####################################################
# QWT
include(${CMAKE_SOURCE_DIR}/cmake/FindQwt.cmake)

####################################################
# GMT
set(WITH_GMT ${DEFAULT_WITH_GMT} CACHE BOOL "Determines is required gmt")
mark_as_advanced(WITH_GMT)
if (WITH_GMT)
    include(${CMAKE_SOURCE_DIR}/extern/gmt/cmake/modules/FindGMT.cmake)
    if (UNIX AND NOT GMT_FOUND)
        message(FATAL_ERROR "GMT not found, cannot proceed")
    endif ()
endif ()

####################################################
# GDAL
find_package(GDAL REQUIRED)
if (NOT GDAL_FOUND)
    message(FATAL_ERROR "GDAL not found, cannot proceed")
endif ()
if (NOT GDAL_CONFIG)
    message(FATAL_ERROR "gdal-config command not found (not in PATH?), cannot proceed")
endif ()

execute_process(
        COMMAND ${GDAL_CONFIG} --version
        OUTPUT_VARIABLE SYSTEM_GDAL_VERSION
)

if (SYSTEM_GDAL_VERSION VERSION_LESS "2.2")
    message(FATAL_ERROR "GDAL version \"${SYSTEM_GDAL_VERSION}\" is too old, at least 2.2 is required")
endif ()

####################################################
# translate
option(UPDATE_TRANSLATIONS "Enable rescanning sources to update .ts files" ON)
file(GLOB_RECURSE TS_SOURCES "src/*.cpp" "src/*.h" "src/*.ui")
set(TS_FILES ${CMAKE_SOURCE_DIR}/i18n/GisL_en.ts ${CMAKE_SOURCE_DIR}/i18n/GisL_zh.ts)

if (UPDATE_TRANSLATIONS)
    message("** parse sources for new translations")
    qt5_create_translation(QM_FILES
            ${TS_FILES}
            ${TS_SOURCES}
            )
else (UPDATE_TRANSLATIONS)
    message("** update qm files")
    qt5_add_translation(QM_FILES
            ${TS_FILES}
            )
endif (UPDATE_TRANSLATIONS)

add_custom_target(Translations DEPENDS ${QM_FILES})

####################################################
# clang-tidy
set(WITH_CLANG_TIDY TRUE CACHE BOOL "Use Clang tidy")
mark_as_advanced(WITH_CLANG_TIDY)
if (WITH_CORE)
    if (WITH_CLANG_TIDY)
        find_program(
                CLANG_TIDY_EXE
                NAMES "clang-tidy"
                DOC "Path to clang-tidy executable"
        )
        if (NOT CLANG_TIDY_EXE)
            message(STATUS "clang-tidy not found.")
        else ()
            message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
            set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*,-cppcoreguidelines*,-readability-implicit-bool-cast,-llvm-include-order,-cert-err58-cpp,-modernize-pass-by-value,-google-readability-braces-around-statements,-modernize-use-auto,-modernize-loop-convert,-readability-else-after-return,-readability-braces-around-statements,-google-runtime-references,-readability-named-parameter,-google-default-arguments,-google-readability-todo,-readability-inconsistent-declaration-parameter-name,-cert-flp30-c,-google-readability-casting,-clang-analyzer-security.FloatLoopCounter,-google-runtime-int,-modernize-use-using,-google-explicit-constructor,-google-build-using-namespace,-cert-err34-c,-clang-analyzer-core.CallAndMessage,-google-readability-function-size,-modernize-make-shared,-modernize-use-nullptr,-clang-analyzer-cplusplus.NewDeleteLeaks,-clang-analyzer-core.NonNullParamChecker,performance-unnecessary-copy-initialization,-readability-simplify-boolean-expr,-modernize-raw-string-literal,-performance-unnecessary-copy-initialization")
        endif ()
    endif ()
endif ()

####################################################
# lib type
set(FORCE_SHARED_LIBS ${DEFAULT_FORCE_SHARED_LIBS} CACHE BOOL "Determines whether libraries should be static only")
mark_as_advanced(FORCE_SHARED_LIBS)
if (FORCE_SHARED_LIBS)
    set(LIBRARY_TYPE SHARED)
else ()
    set(LIBRARY_TYPE STATIC)
endif ()

####################################################
# ui
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src/ui)

####################################################
# choose modules
set(WITH_ANALYSIS TRUE CACHE BOOL "Determines whether GisL analysis library should be built")

####################################################
# main app
add_subdirectory(${CMAKE_SOURCE_DIR}/extern)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
set(TEST_DATA_DIR
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/data/")

configure_file(
        "${CMAKE_SOURCE_DIR}/src/gisl_config.h.in"
        "${CMAKE_BINARY_DIR}/src/gisl_config.h"
)
