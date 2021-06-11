cmake_minimum_required(VERSION 3.10)

SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "6")
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

find_package(absl REQUIRED)

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

add_subdirectory(tests)

set(GISL_CODECVT_SRCS
        src/codecvt/dacodecvt.cpp
        src/codecvt/dacodecvt.h
        src/codecvt/dadecoder.cpp
        src/codecvt/dadecoder.h
        src/codecvt/daencoder.cpp
        src/codecvt/daencoder.h
        src/codecvt/daunit.cpp
        src/codecvt/daunit.h
        )
set(GISL_CORE_VACTOR_SRCS
        src/core/vector/featureproperty.cpp
        src/core/vector/featureproperty.h
        src/core/vector/layerpropertytable.cpp
        src/core/vector/layerpropertytable.h
        src/core/vector/vectorfeature.cpp
        src/core/vector/vectorfeature.h
        src/core/vector/vectorlayer.cpp
        src/core/vector/vectorlayer.h
        )
set(GISL_CORE_PROVIDER_SRCS
        src/core/provider/dataprovider.h
        src/core/provider/dataprovider.cpp
        src/core/provider/rasterprovider.cpp
        src/core/provider/rasterprovider.h
        src/core/provider/vectorprovider.cpp
        src/core/provider/vectorprovider.h
        )
set(GISL_CORE_LAYER_SRCS
        src/core/layer/layertree.cpp
        src/core/layer/layertree.h
        src/core/layer/layer.cpp
        src/core/layer/layer.h
        )
set(GISL_CORE_RASTER_SRCS
        src/core/raster/rasterband.cpp
        src/core/raster/rasterband.h
        )
set(GISL_CORE_RENDER_SRCS
#        src/core/render/
#        src/core/geometry/rectangle.h
        )
set(GISL_CORE_GEO_SRCS
        src/core/geometry/abstractgeometry.cpp
        src/core/geometry/abstractgeometry.h
        src/core/geometry/geometryfactory.cpp
        src/core/geometry/geometryfactory.h
        src/core/geometry/geomlinestring.cpp
        src/core/geometry/geomlinestring.h
        src/core/geometry/geommultilinestring.cpp
        src/core/geometry/geommultilinestring.h
        src/core/geometry/geommultipoint.cpp
        src/core/geometry/geommultipoint.h
        src/core/geometry/geommultipolygon.cpp
        src/core/geometry/geommultipolygon.h
        src/core/geometry/geompoint.cpp
        src/core/geometry/geompoint.h
        src/core/geometry/geompolygon.cpp
        src/core/geometry/geompolygon.h
        src/core/geometry/rectangle.cpp
        src/core/geometry/rectangle.h
        )

set(GISL_CORE_SRCS
        ${GISL_CORE_GEO_SRCS}
        ${GISL_CORE_RENDER_SRCS}
        ${GISL_CORE_RASTER_SRCS}
        ${GISL_CORE_PROVIDER_SRCS}
        ${GISL_CORE_VACTOR_SRCS}
        ${GISL_CORE_LAYER_SRCS}
        src/core/coordinatetransform.cpp
        src/core/coordinatetransform.h
        src/core/layer/layertree.cpp
        src/core/layer/layertree.h
        src/core/spatialreference.cpp
        src/core/spatialreference.h
        )
set(GISL_GUI_COMMAND_SRCS
        src/gui/command/command.cpp
        src/gui/command/command.h
        src/gui/command/commandhistory.cpp
        src/gui/command/commandhistory.h
        src/gui/command/opensldcommand.cpp
        src/gui/command/opensldcommand.h
        src/gui/command/openrastercommand.cpp
        src/gui/command/openrastercommand.h
        src/gui/command/openvectorcommand.cpp
        src/gui/command/openvectorcommand.h
        )
set(GISL_GUI_PAINTER_SRCS
        src/gui/painter/glpainterfactory.cpp
        src/gui/painter/glpainterfactory.h
        src/gui/painter/painterfactory.cpp
        src/gui/painter/painterfactory.h
        )
set(GISL_GUI_SYMBOLIZER_SRCS
        src/gui/symbolizer/abstractsymbolizer.cpp
        src/gui/symbolizer/abstractsymbolizer.h
        src/gui/symbolizer/polygonsymbolizer.cpp
        src/gui/symbolizer/polygonsymbolizer.h
        src/gui/symbolizer/symbolizerfactory.cpp
        src/gui/symbolizer/symbolizerfactory.h
        src/gui/symbolizer/textsymbolizer.cpp
        src/gui/symbolizer/textsymbolizer.h
        )
set(GISL_GUI_SRCS
        ${GISL_GUI_COMMAND_SRCS}
        ${GISL_GUI_PAINTER_SRCS}
        ${GISL_GUI_SYMBOLIZER_SRCS}
        src/gui/editmenu.cpp
        src/gui/editmenu.h
        src/gui/glcanvas.cpp
        src/gui/glcanvas.h
        src/gui/layerrender.cpp
        src/gui/layerrender.h
        src/gui/mainwindow.cpp
        src/gui/mainwindow.h
        src/gui/menubar.cpp
        src/gui/menubar.h
        src/gui/sld.cpp
        src/gui/sld.h
        )
set(GISL_UTILS_SRCS
        src/utils/log.cpp
        src/utils/log.h
        src/utils/ptroperate.cpp
        src/utils/ptroperate.h
        src/utils/stringoperate.cpp
        src/utils/stringoperate.h
        src/utils/xml.cpp
        src/utils/xml.h
        )

add_library(gisl_static_lib STATIC
        ${GISL_CORE_SRCS}
        ${GISL_GUI_SRCS}
        ${GISL_UTILS_SRCS}
        ${GISL_CODECVT_SRCS}
        )

target_link_libraries(gisl_static_lib
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        ${GDAL_LIBRARY}
        absl::strings
        )

# main core software
add_executable(gisl
        src/main.cpp
        )

target_link_libraries(gisl
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        gisl_static_lib
        )
