cmake_minimum_required(VERSION 3.10)

SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "4")
SET(CPACK_PACKAGE_VERSION_PATCH "1")
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
message(STATUS "include Qt")
include(${CMAKE_SOURCE_DIR}/cmake/myQtConfig.cmake)
find_package(QT NAMES Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# GDAL
include(${CMAKE_SOURCE_DIR}/cmake/FindGDAL.cmake)

# OpenGL
include(${CMAKE_SOURCE_DIR}/cmake/OpenGLConfig.cmake)

# main gis software
add_executable(GisL
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/codecvt/daunit.cpp src/codecvt/daunit.h src/codecvt/dacodecvt.cpp src/codecvt/dacodecvt.h src/codecvt/dadecoder.cpp src/codecvt/dadecoder.h src/codecvt/daencoder.cpp src/codecvt/daencoder.h
        src/plot/sld.cpp src/plot/sld.h src/plot/render.cpp src/plot/render.h
        src/gis/vector.cpp src/gis/vectorlayer.cpp src/gis/vectorfeature.cpp src/gis/spatialreference.cpp src/gis/geometry.cpp src/gis/geopoint.cpp src/gis/geoline.cpp src/gis/geopolygon.cpp src/gis/geomultipoint.cpp src/gis/geomultiline.cpp src/gis/geomultipolygon.cpp
        src/gis/vector.h src/gis/vectorlayer.h
        src/gis/vectorfeature.h src/gis/spatialreference.h
        src/gis/geometry.h src/gis/geopoint.h
        src/gis/geoline.h src/gis/geopolygon.h
        src/gis/geomultipoint.h src/gis/geomultiline.h
        src/gis/geomultipolygon.h
        )

target_link_libraries(GisL
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        GDAL
        OpenGL GLUT
        )

add_executable(GisTest
        tests/gistest.cpp
        #        src/gis/geopoint.cpp src/gis/geopoint.h
        #        src/gis/geoline.cpp src/gis/geoline.h
        #        src/gis/geopolygon.cpp src/gis/geopolygon.h
        #        src/gis/geomultipoint.cpp src/gis/geomultipoint.h
        #        src/gis/geomultiline.cpp src/gis/geomultiline.h
        #        src/gis/geomultipolygon.cpp src/gis/geomultipolygon.h
        #        src/gis/geofeature.cpp src/gis/geofeature.h
        src/gis/vector.cpp src/gis/vectorlayer.cpp
        src/gis/vectorfeature.cpp src/gis/spatialreference.cpp
        src/gis/geometry.cpp src/gis/geopoint.cpp
        src/gis/geoline.cpp src/gis/geopolygon.cpp
        src/gis/geomultipoint.cpp src/gis/geomultiline.cpp
        src/gis/geomultipolygon.cpp src/gis/vector.h src/gis/vectorlayer.h
        src/gis/vectorfeature.h src/gis/spatialreference.h
        src/gis/geometry.h src/gis/geopoint.h
        src/gis/geoline.h src/gis/geopolygon.h
        src/gis/geomultipoint.h src/gis/geomultiline.h
        src/gis/geomultipolygon.h
        src/utils/stringoperate.cpp src/utils/stringoperate.h)
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

## KkGis
#include_directories(external/KkGis)
#aux_source_directory(KkGis external/KkGis)
#add_executable(KkGis
#        ${KkGis})
#
#target_link_libraries(KkGis Qt${QT_VERSION_MAJOR}::Widgets)
#
## MmGis
#include_directories(external/MmGis)
#aux_source_directory(MmGis external/MmGis)
#add_executable(MmGis
#        ${MmGis})
#
#target_link_libraries(MmGis Qt${QT_VERSION_MAJOR}::Widgets)

#include(GNUInstallDirs)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
#
#set(GISL_CODECVT_DIR ${CMAKE_SOURCE_DIR}/src/codecvt)
#set(GISL_CODECVT_SRCS
#        ${GISL_CODECVT_DIR}/dacodecvt.cpp ${GISL_CODECVT_DIR}/dadecoder.cpp ${GISL_CODECVT_DIR}/daencoder.cpp ${GISL_CODECVT_DIR}/daunit.cpp)
#set(GISL_CODECVT_HDRS
#        ${GISL_CODECVT_DIR}/dacodecvt.h ${GISL_GIS_DIR}/${GISL_CODECVT_DIR}/dadecoder.h ${GISL_GIS_DIR}/${GISL_CODECVT_DIR}/daencoder.h ${GISL_GIS_DIR}/${GISL_CODECVT_DIR}/daunit.h)
#
#set(GISL_GIS_DIR ${CMAKE_SOURCE_DIR}/src/gis)
#set(GISL_GIS_SRCS
#        ${GISL_GIS_DIR}/vector.cpp ${GISL_GIS_DIR}/vectorlayer.cpp ${GISL_GIS_DIR}/vectorfeature.cpp ${GISL_GIS_DIR}/spatialreference.cpp ${GISL_GIS_DIR}/geometry.cpp ${GISL_GIS_DIR}/geopoint.cpp ${GISL_GIS_DIR}/geoline.cpp ${GISL_GIS_DIR}/geopolygon.cpp ${GISL_GIS_DIR}/geomultipoint.cpp ${GISL_GIS_DIR}/geomultiline.cpp ${GISL_GIS_DIR}/geomultipolygon.cpp)
#set(GISL_GIS_HDRS
#        ${GISL_GIS_DIR}/vector.h ${GISL_GIS_DIR}/vectorlayer.h ${GISL_GIS_DIR}/vectorfeature.h ${GISL_GIS_DIR}/spatialreference.h ${GISL_GIS_DIR}/geometry.h ${GISL_GIS_DIR}/geopoint.h ${GISL_GIS_DIR}/geoline.h ${GISL_GIS_DIR}/geopolygon.h ${GISL_GIS_DIR}/geomultipoint.h ${GISL_GIS_DIR}/geomultiline.h ${GISL_GIS_DIR}/geomultipolygon.h)
#
#set(GISL_PLOT_DIR ${CMAKE_SOURCE_DIR}/src/plot)
#set(GISL_PLOT_SRCS
#        ${GISL_PLOT_DIR}/render.cpp ${GISL_PLOT_DIR}/sld.cpp)
#set(GISL_PLOT_HDRS
#        ${GISL_PLOT_DIR}/render.h ${GISL_PLOT_DIR}/sld.h)
#
#set(GISL_UTILS_DIR ${CMAKE_SOURCE_DIR}/src/utils)
#set(GISL_UTILS_SRCS
#        ${GISL_UTILS_DIR}/merror.cpp ${GISL_UTILS_DIR}/stringoperate.cpp)
#set(GISL_UTILS_HDRS
#        ${GISL_UTILS_DIR}/merror.h ${GISL_UTILS_DIR}/stringoperate.h)
#
##
#include_directories(
#        src/codecvt
#        src/gis
#        src/plot
#        src/utils)
#
#aux_source_directory(src/codecvt   GISL_CODECVT_SUBDIR )
#aux_source_directory(src/gis       GISL_GIS_SUBDIR     )
#aux_source_directory(src/plot      GISL_PLOT_SUBDIR    )
#aux_source_directory(src/utils     GISL_UTILS_SUBDIR   )
#
#
## defines targets and sources
#add_subdirectory(src)
#
## contains an "external" library we will link to
##add_subdirectory(external)
#
## enable testing and define tests
#enable_testing()
#add_subdirectory(tests)
#
#
#
### main gis software
#add_executable(GisL
#        src/main.cpp
#        src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui
#        ${GISL_CODECVT_SUBDIR} ${GISL_GIS_SUBDIR} ${GISL_PLOT_SUBDIR} ${GISL_UTILS_SUBDIR})
#
#target_link_libraries(GisL Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(GisL GDAL)
#target_link_libraries(GisL OpenGL GLUT)
#
## GisTest
##add_executable(GisTest
##        tests/gistest.cpp
##        ${GIS_SRCS})
##target_link_libraries(GisTest GDAL)
#
## CodecvtTest
##add_executable(CodecvtTest
##        tests/codecvttest.cpp
##        ${CODECVT_SRCS})
#
### KkGis
##include_directories(external/KkGis)
##aux_source_directory(KkGis external/KkGis)
##add_executable(KkGis
##        ${KkGis})
#
##target_link_libraries(KkGis Qt${QT_VERSION_MAJOR}::Widgets)
#
### MmGis
##include_directories(external/MmGis)
##aux_source_directory(MmGis external/MmGis)
##add_executable(MmGis
##        ${MmGis})
##
##target_link_libraries(MmGis Qt${QT_VERSION_MAJOR}::Widgets)
#
