cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0079 NEW)

SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "7")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(COMPLETE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
project(GisL LANGUAGES CXX VERSION ${COMPLETE_VERSION})

set(QT_VERSION_MAJOR 5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set path to additional CMake modules
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# get the current working branch
execute_process(
        COMMAND git describe --all --dirty
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE GISL_GIT_DESCRIPTION
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# last commit hash
execute_process(
        COMMAND git log -1 --format=%H
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE GISL_GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(TIMESTAMP TNTN_TIMESTAMP "%Y%m%dT%H%MZ" UTC)

# Doxygen
message(STATUS "Build documentation open")
include(${CMAKE_SOURCE_DIR}/cmake/build_doxygen.cmake)
build_doxygen()

# Sphinx
include(${CMAKE_SOURCE_DIR}/cmake/FindSphinx.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/UseSphinxDoc.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/UseBreathe.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/mySphinxConfig.cmake)

# Qt
#include(${CMAKE_SOURCE_DIR}/cmake/myQtConfig.cmake)
#find_package(QT NAMES Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Gui LinguistTools REQUIRED)
find_package(Qt5 COMPONENTS Widgets Gui LinguistTools REQUIRED)

# QWT
include(${CMAKE_SOURCE_DIR}/cmake/FindQwt.cmake)

# absl
find_package(absl REQUIRED)

# GMT
include(${CMAKE_SOURCE_DIR}/extern/gmt/cmake/modules/FindGMT.cmake)
if (UNIX AND NOT GMT_FOUND)
    message(FATAL_ERROR "GMT not found, cannot proceed")
endif ()

# Eigen
find_package(Eigen3 REQUIRED)

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

set(FORCE_STATIC_LIBS ${DEFAULT_FORCE_STATIC_LIBS} CACHE BOOL "Determines whether libraries should be static only")
mark_as_advanced(FORCE_STATIC_LIBS)
if (FORCE_STATIC_LIBS)
    set(LIBRARY_TYPE STATIC)
else ()
    set(LIBRARY_TYPE SHARED)
endif ()

add_subdirectory(src)
add_subdirectory(tests)
