cmake_minimum_required(VERSION 3.10)

SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "3")
SET(CPACK_PACKAGE_VERSION_PATCH "10")
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

# main gis software
add_executable(GisL
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/codecvt/daunit.cpp src/codecvt/daunit.h src/codecvt/dacodecvt.cpp src/codecvt/dacodecvt.h src/codecvt/dadecoder.cpp src/codecvt/dadecoder.h src/codecvt/daencoder.cpp src/codecvt/daencoder.h
        src/plot/sld.cpp src/plot/sld.h src/plot/layer.cpp src/plot/layer.h
        src/gis/geopoint.cpp src/gis/geopoint.h src/gis/geoline.cpp src/gis/geoline.h src/gis/geopolygon.cpp src/gis/geopolygon.h src/gis/geomultipoint.cpp src/gis/geomultipoint.h src/gis/geomultiline.cpp src/gis/geomultiline.h src/gis/geomultipolygon.cpp src/gis/geomultipolygon.h src/gis/vector.cpp src/gis/vector.h src/gis/spatialreference.cpp src/gis/spatialreference.h src/gis/vectorlayer.cpp src/gis/vectorlayer.h src/gis/vectorfeature.cpp src/gis/vectorfeature.h src/gis/geometry.cpp src/gis/geometry.h
        src/utils/stringoperate.cpp src/utils/stringoperate.h)

target_link_libraries(GisL Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(GisL ${GDAL_LIBRARY})
target_link_libraries(GisL GDAL)

add_executable(GeoTest
        src/test/gistest.cpp
        src/gis/geopoint.cpp src/gis/geopoint.h
        src/gis/geoline.cpp src/gis/geoline.h
        src/gis/geopolygon.cpp src/gis/geopolygon.h
        src/gis/geomultipoint.cpp src/gis/geomultipoint.h
        src/gis/geomultiline.cpp src/gis/geomultiline.h
        src/gis/geomultipolygon.cpp src/gis/geomultipolygon.h
        src/gis/vector.cpp src/gis/vector.h
        src/gis/spatialreference.cpp src/gis/spatialreference.h
        src/gis/vectorlayer.cpp src/gis/vectorlayer.h
        src/gis/vectorfeature.cpp src/gis/vectorfeature.h
        src/gis/geometry.cpp src/gis/geometry.h
        src/utils/stringoperate.cpp src/utils/stringoperate.h)
#target_link_libraries(GeoTest ${GDAL_LIBRARY})
target_link_libraries(GeoTest GDAL)

# codecvt
add_executable(Codecvt
        src/test/codecvttest.cpp
        src/codecvt/daunit.cpp
        src/codecvt/daunit.h
        src/codecvt/dacodecvt.cpp
        src/codecvt/dacodecvt.h
        src/codecvt/dadecoder.cpp
        src/codecvt/dadecoder.h
        src/codecvt/daencoder.cpp
        src/codecvt/daencoder.h)

# KkGis
include_directories(external/KkGis)
aux_source_directory(KkGis external/KkGis)
add_executable(KkGis
        ${KkGis})

target_link_libraries(KkGis Qt${QT_VERSION_MAJOR}::Widgets)

# MmGis
include_directories(external/MmGis)
aux_source_directory(MmGis external/MmGis)
add_executable(MmGis
        ${MmGis})

target_link_libraries(MmGis Qt${QT_VERSION_MAJOR}::Widgets)