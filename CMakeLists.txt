cmake_minimum_required(VERSION 3.10)

SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "5")
SET(CPACK_PACKAGE_VERSION_PATCH "2")
SET(COMPLETE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
project(GisL LANGUAGES CXX VERSION ${COMPLETE_VERSION})

set(QT_VERSION_MAJOR 5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set path to additional CMake modules
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

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
include(${CMAKE_SOURCE_DIR}/cmake/myQtConfig.cmake)
find_package(QT NAMES Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Gui LinguistTools REQUIRED)
find_package(Qt5 COMPONENTS Widgets Gui LinguistTools REQUIRED)

# GDAL
include(${CMAKE_SOURCE_DIR}/cmake/FindGDAL.cmake)

# OpenGL
include(${CMAKE_SOURCE_DIR}/cmake/OpenGLConfig.cmake)
#find_package(Qt{QT_VERSION_MAJOR}::Gui)

# TinyXML2
#find_package(tinyxml2)

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

file(GLOB_RECURSE GISL_SRCS "src/*.cpp" "src/*.h")
file(GLOB_RECURSE GISL_CORE_SRCS "src/core/*.cpp" "src/core/*.h")
file(GLOB_RECURSE GISL_GUI_SRCS "src/gui/*.cpp" "src/gui/*.h")

# main core software
add_executable(GisL
        ${GISL_SRCS})

target_link_libraries(GisL
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        ${Qt5Gui_LIBRARIES}
        ${GDAL_LIBRARY}
        OpenGL
        #        GLUT
        )
#qt5_use_modules(GisL Widgets Gui)

add_executable(GisTest
        tests/gistest.cpp
        ${GISL_CORE_SRCS}
        src/utils/gislobject.cpp src/utils/gislobject.h
        src/utils/stringoperate.cpp src/utils/stringoperate.h
        src/utils/ptroperate.cpp src/utils/ptroperate.h
        src/utils/log.cpp src/utils/log.h)
target_link_libraries(GisTest
        PUBLIC
        ${GDAL_LIBRARY})

# Codecvt
add_executable(Codecvt
        tests/codecvttest.cpp
        src/codecvt/daunit.cpp
        src/codecvt/daunit.h
        src/codecvt/dacodecvt.cpp
        src/codecvt/dacodecvt.h
        src/codecvt/dadecoder.cpp
        src/codecvt/dadecoder.h
        src/codecvt/daencoder.cpp
        src/codecvt/daencoder.h)

# PlotTest
add_executable(PlotTest
        tests/plottest.cpp
        src/utils/gislobject.cpp src/utils/gislobject.h
        src/gui/sld.cpp src/gui/sld.h
        src/gui/layerrender.cpp src/gui/layerrender.h
        src/utils/xml.cpp src/utils/xml.h
        src/utils/stringoperate.cpp src/utils/stringoperate.h
        src/gui/symbolizer/polygonsymbolizer.cpp src/gui/symbolizer/polygonsymbolizer.h
        src/gui/symbolizer/textsymbolizer.cpp src/gui/symbolizer/textsymbolizer.h
        src/gui/symbolizer/abstractsymbolizer.cpp src/gui/symbolizer/abstractsymbolizer.h src/utils/log.cpp src/utils/log.h)

target_link_libraries(PlotTest
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(lwtree tests/treeb.cpp src/utils/log.cpp src/utils/log.h)

add_executable(utilsTest
        tests/utilstest.cpp
        src/utils/stringoperate.cpp src/utils/stringoperate.h
        src/utils/ptroperate.h src/utils/ptroperate.cpp
        src/utils/log.cpp src/utils/log.h)
target_link_libraries(utilsTest
        PUBLIC
        )

