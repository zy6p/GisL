cmake_minimum_required(VERSION 3.10)

SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "4")
SET(CPACK_PACKAGE_VERSION_PATCH "3")
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
#set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/codecvt ${CMAKE_SOURCE_DIR}/src/core ${CMAKE_SOURCE_DIR}/src/paint ${CMAKE_SOURCE_DIR}/src/utils)

# Sphinx
include(${CMAKE_SOURCE_DIR}/cmake/FindSphinx.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/UseSphinxDoc.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/UseBreathe.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/mySphinxConfig.cmake)

# Qt
include(${CMAKE_SOURCE_DIR}/cmake/myQtConfig.cmake)
find_package(QT NAMES Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)

# GDAL
include(${CMAKE_SOURCE_DIR}/cmake/FindGDAL.cmake)

# OpenGL
#include(${CMAKE_SOURCE_DIR}/cmake/OpenGLConfig.cmake)
#find_package(Qt{QT_VERSION_MAJOR}::Gui)

# TinyXML2
#find_package(tinyxml2)

# main core software
add_executable(GisL
        src/main.cpp
        src/gui/mainwindow.cpp
        src/gui/mainwindow.h
        src/gui/mainwindow.ui
        src/utils/gislobject.cpp src/utils/gislobject.h
        src/codecvt/daunit.cpp src/codecvt/daunit.h src/codecvt/dacodecvt.cpp src/codecvt/dacodecvt.h src/codecvt/dadecoder.cpp src/codecvt/dadecoder.h src/codecvt/daencoder.cpp src/codecvt/daencoder.h
        src/gui/sld.cpp src/gui/sld.h src/gui/layerrender.cpp src/gui/layerrender.h
        src/core/vector.cpp src/core/vectorlayer.cpp src/core/vectorfeature.cpp src/core/spatialreference.cpp src/core/geometry.cpp src/core/geopoint.cpp src/core/geoline.cpp src/core/geopolygon.cpp src/core/geomultipoint.cpp src/core/geomultiline.cpp src/core/geomultipolygon.cpp
        src/core/vector.h src/core/vectorlayer.h
        src/core/vectorfeature.h src/core/spatialreference.h
        src/core/geometry.h src/core/geopoint.h
        src/core/geoline.h src/core/geopolygon.h
        src/core/geomultipoint.h src/core/geomultiline.h
        src/core/geomultipolygon.h
        src/utils/xml.cpp src/utils/xml.h
        src/utils/stringoperate.h src/utils/stringoperate.cpp
        src/core/featureproperty.cpp src/core/featureproperty.h
        src/core/layerpropertytable.cpp src/core/layerpropertytable.h
        src/gui/glcanvas.cpp src/gui/glcanvas.h src/gui/menubar.cpp
        src/gui/menubar.h src/utils/ptroperate.cpp src/utils/ptroperate.h
        src/gui/gui.qrc src/gui/symbolizer/polygonsymbolizer.cpp src/gui/symbolizer/polygonsymbolizer.h src/gui/symbolizer/textsymbolizer.cpp src/gui/symbolizer/textsymbolizer.h src/gui/symbolizer/symbolizer.cpp src/gui/symbolizer/symbolizer.h)

target_link_libraries(GisL
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        ${Qt5Gui_LIBRARIES}
        ${GDAL_LIBRARY}
        #        #        ${OpenGL_LIBRARY} ${GLUT_LIBRARY}
        )
#qt5_use_modules(GisL Widgets Gui)

add_executable(GisTest
        tests/gistest.cpp
        #        src/core/geopoint.cpp src/core/geopoint.h
        #        src/core/geoline.cpp src/core/geoline.h
        #        src/core/geopolygon.cpp src/core/geopolygon.h
        #        src/core/geomultipoint.cpp src/core/geomultipoint.h
        #        src/core/geomultiline.cpp src/core/geomultiline.h
        #        src/core/geomultipolygon.cpp src/core/geomultipolygon.h
        #        src/core/geofeature.cpp src/core/geofeature.h
        src/utils/gislobject.cpp src/utils/gislobject.h
        src/core/vector.cpp src/core/vectorlayer.cpp
        src/core/vectorfeature.cpp src/core/spatialreference.cpp
        src/core/geometry.cpp src/core/geopoint.cpp
        src/core/geoline.cpp src/core/geopolygon.cpp
        src/core/geomultipoint.cpp src/core/geomultiline.cpp
        src/core/geomultipolygon.cpp src/core/vector.h src/core/vectorlayer.h
        src/core/vectorfeature.h src/core/spatialreference.h
        src/core/geometry.h src/core/geopoint.h
        src/core/geoline.h src/core/geopolygon.h
        src/core/geomultipoint.h src/core/geomultiline.h
        src/core/geomultipolygon.h
        src/utils/stringoperate.cpp src/utils/stringoperate.h
        src/core/featureproperty.cpp src/core/featureproperty.h
        src/core/layerpropertytable.cpp src/core/layerpropertytable.h
        src/utils/ptroperate.cpp src/utils/ptroperate.h)
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
        src/utils/stringoperate.cpp src/utils/stringoperate.h)

target_link_libraries(PlotTest
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(lwtree tests/treeb.cpp)

add_executable(utilsTest
        tests/utilstest.cpp
        src/utils/stringoperate.cpp src/utils/stringoperate.h
        src/utils/ptroperate.h src/utils/ptroperate.cpp
        )


## main core software
#add_executable(GisL
#        src/main.cpp
#        src/mainwindow.cpp
#        src/mainwindow.h
#        src/mainwindow.ui
#        src/codecvt/daunit.cpp src/codecvt/daunit.h src/codecvt/dacodecvt.cpp src/codecvt/dacodecvt.h src/codecvt/dadecoder.cpp src/codecvt/dadecoder.h src/codecvt/daencoder.cpp src/codecvt/daencoder.h
#        src/paint/sld.cpp src/paint/sld.h src/paint/layer.cpp src/paint/layer.h
#        src/core/geopoint.cpp src/core/geopoint.h src/core/geoline.cpp src/core/geoline.h src/core/geopolygon.cpp src/core/geopolygon.h src/core/geomultipoint.cpp src/core/geomultipoint.h src/core/geomultiline.cpp src/core/geomultiline.h src/core/geomultipolygon.cpp src/core/geomultipolygon.h src/core/vector.cpp src/core/vector.h src/core/spatialreference.cpp src/core/spatialreference.h src/core/vectorlayer.cpp src/core/vectorlayer.h src/core/vectorfeature.cpp src/core/vectorfeature.h src/core/geometry.cpp src/core/geometry.h
#        src/utils/stringoperate.cpp src/utils/stringoperate.h)
#
#target_link_libraries(GisL Qt${QT_VERSION_MAJOR}::Widgets)
##target_link_libraries(GisL ${GDAL_LIBRARY})
#target_link_libraries(GisL GDAL)
#
#add_executable(GeoTest
#        src/test/gistest.cpp
#        src/core/geopoint.cpp src/core/geopoint.h
#        src/core/geoline.cpp src/core/geoline.h
#        src/core/geopolygon.cpp src/core/geopolygon.h
#        src/core/geomultipoint.cpp src/core/geomultipoint.h
#        src/core/geomultiline.cpp src/core/geomultiline.h
#        src/core/geomultipolygon.cpp src/core/geomultipolygon.h
#        src/core/vector.cpp src/core/vector.h
#        src/core/spatialreference.cpp src/core/spatialreference.h
#        src/core/vectorlayer.cpp src/core/vectorlayer.h
#        src/core/vectorfeature.cpp src/core/vectorfeature.h
#        src/core/geometry.cpp src/core/geometry.h
#        src/utils/stringoperate.cpp src/utils/stringoperate.h)
##target_link_libraries(GeoTest ${GDAL_LIBRARY})
#target_link_libraries(GeoTest GDAL)
#
## codecvt
#add_executable(Codecvt
#        src/test/codecvttest.cpp
#        src/codecvt/daunit.cpp
#        src/codecvt/daunit.h
#        src/codecvt/dacodecvt.cpp
#        src/codecvt/dacodecvt.h
#        src/codecvt/dadecoder.cpp
#        src/codecvt/dadecoder.h
#        src/codecvt/daencoder.cpp
#        src/codecvt/daencoder.h)

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
#set(GISL_GIS_DIR ${CMAKE_SOURCE_DIR}/src/core)
#set(GISL_GIS_SRCS
#        ${GISL_GIS_DIR}/vector.cpp ${GISL_GIS_DIR}/vectorlayer.cpp ${GISL_GIS_DIR}/vectorfeature.cpp ${GISL_GIS_DIR}/spatialreference.cpp ${GISL_GIS_DIR}/geometry.cpp ${GISL_GIS_DIR}/geopoint.cpp ${GISL_GIS_DIR}/geoline.cpp ${GISL_GIS_DIR}/geopolygon.cpp ${GISL_GIS_DIR}/geomultipoint.cpp ${GISL_GIS_DIR}/geomultiline.cpp ${GISL_GIS_DIR}/geomultipolygon.cpp)
#set(GISL_GIS_HDRS
#        ${GISL_GIS_DIR}/vector.h ${GISL_GIS_DIR}/vectorlayer.h ${GISL_GIS_DIR}/vectorfeature.h ${GISL_GIS_DIR}/spatialreference.h ${GISL_GIS_DIR}/geometry.h ${GISL_GIS_DIR}/geopoint.h ${GISL_GIS_DIR}/geoline.h ${GISL_GIS_DIR}/geopolygon.h ${GISL_GIS_DIR}/geomultipoint.h ${GISL_GIS_DIR}/geomultiline.h ${GISL_GIS_DIR}/geomultipolygon.h)
#
#set(GISL_PLOT_DIR ${CMAKE_SOURCE_DIR}/src/paint)
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
#        src/core
#        src/paint
#        src/utils)
#
#aux_source_directory(src/codecvt   GISL_CODECVT_SUBDIR )
#aux_source_directory(src/core       GISL_GIS_SUBDIR     )
#aux_source_directory(src/paint      GISL_PLOT_SUBDIR    )
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
### main core software
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
