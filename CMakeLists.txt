cmake_minimum_required(VERSION 3.17.1)

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
        src/Codecvt/daunit.cpp src/Codecvt/daunit.h src/Codecvt/dacodecvt.cpp src/Codecvt/dacodecvt.h src/Codecvt/dadecoder.cpp src/Codecvt/dadecoder.h src/Codecvt/daencoder.cpp src/Codecvt/daencoder.h
        src/Plot/sld.cpp src/Plot/sld.h src/Plot/layer.cpp src/Plot/layer.h
        src/Geo/geopoint.cpp src/Geo/geopoint.h src/Geo/geoline.cpp src/Geo/geoline.h src/Geo/geopolygon.cpp src/Geo/geopolygon.h src/Geo/geomultipoint.cpp src/Geo/geomultipoint.h src/Geo/geomultiline.cpp src/Geo/geomultiline.h src/Geo/geomultipolygon.cpp src/Geo/geomultipolygon.h src/Geo/geofeature.cpp src/Geo/geofeature.h src/Geo/crs.cpp src/Geo/crs.h src/utils/stringoperate.cpp src/utils/stringoperate.h)

target_link_libraries(GisL Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(GisL ${GDAL_LIBRARY})

add_executable(GeoTest
        src/Geo/mian.cpp
        src/Geo/geopoint.cpp src/Geo/geopoint.h
        src/Geo/geoline.cpp src/Geo/geoline.h
        src/Geo/geopolygon.cpp src/Geo/geopolygon.h
        src/Geo/geomultipoint.cpp src/Geo/geomultipoint.h
        src/Geo/geomultiline.cpp src/Geo/geomultiline.h
        src/Geo/geomultipolygon.cpp src/Geo/geomultipolygon.h
        src/Geo/geofeature.cpp src/Geo/geofeature.h
        src/Geo/crs.cpp src/Geo/crs.h src/utils/stringoperate.cpp src/utils/stringoperate.h)
target_link_libraries(GeoTest ${GDAL_LIBRARY})

# Codecvt
add_executable(FILECODER
        src/Codecvt/main.cpp
        src/Codecvt/daunit.cpp
        src/Codecvt/daunit.h
        src/Codecvt/dacodecvt.cpp
        src/Codecvt/dacodecvt.h
        src/Codecvt/dadecoder.cpp
        src/Codecvt/dadecoder.h
        src/Codecvt/daencoder.cpp
        src/Codecvt/daencoder.h)

# KkGis
include_directories(KkGis)
aux_source_directory(KkGis KkGis)
add_executable(KkGis
        ${KkGis})

target_link_libraries(KkGis Qt${QT_VERSION_MAJOR}::Widgets)

# MmGis
include_directories(MmGis)
aux_source_directory(MmGis MmGis)
add_executable(MmGis
        ${MmGis})

target_link_libraries(MmGis Qt${QT_VERSION_MAJOR}::Widgets)