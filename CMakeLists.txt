cmake_minimum_required(VERSION 3.17.1)

SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "3")
SET(CPACK_PACKAGE_VERSION_PATCH "8")
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
include(cmake/build_doxygen.cmake)
build_doxygen()

# Qt
if (WIN32)
    set(CMAKE_PREFIX_PATH C:/ProgramXXX/Qt/Tools/mingw810_64/)
    set(QT5_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5/)
    set(Qt5Core_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Core/)
    set(Qt5Gui_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Gui/)
    set(Qt5Widgets_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Widgets/)
    set(Qt5_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5/)
    set(QT_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5/)
    set(QtCore_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Core/)
    set(QtGui_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Gui/)
    set(QtWidgets_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Widgets/)
    set(Qt_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5/)

    LIST(APPEND CMAKE_MOUDLE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

    #    set(SRC_LIST C:/ProgramXXX/Qt/5.15.1/mingw81_64/bin/)
    #    add_executable(${PROJECT_NAME} ${SRC_LIST})
    #    target_link_libraries(${PROJECT_NAME} libgcc_s_seh-1)

    # environment:QT_QPA_PLATFORM_PLUGIN_PATH=C:/ProgramXXX/Qt/5.15.1/mingw81_64/plugins/platforms/

    #-GNinja
    #-DCMAKE_BUILD_TYPE:String=Debug
    #-DQT_QMAKE_EXECUTABLE:STRING=%{Qt:qmakeExecutable}
    #-DCMAKE_PREFIX_PATH:STRING=%{Qt:QT_INSTALL_PREFIX}
    #-DCMAKE_C_COMPILER:STRING=%{Compiler:Executable:C}
    #-DCMAKE_CXX_COMPILER:STRING=%{Compiler:Executable:Cxx}
endif ()

find_package(QT NAMES Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# main gis software
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/FileCoder/daunit.cpp src/FileCoder/daunit.h src/FileCoder/filecoder.cpp src/FileCoder/filecoder.h src/FileCoder/dadecoder.cpp src/FileCoder/dadecoder.h src/FileCoder/daencoder.cpp src/FileCoder/daencoder.h
        src/Plot/sld.cpp src/Plot/sld.h src/Plot/layer.cpp src/Plot/layer.h
        src/Geo/geopoint.cpp src/Geo/geopoint.h src/Geo/geoline.cpp src/Geo/geoline.h src/Geo/geopolygon.cpp src/Geo/geopolygon.h src/Geo/geomultipoint.cpp src/Geo/geomultipoint.h src/Geo/geomultiline.cpp src/Geo/geomultiline.h src/Geo/geomultipolygon.cpp src/Geo/geomultipolygon.h src/Geo/geofeature.cpp src/Geo/geofeature.h src/Geo/crs.cpp src/Geo/crs.h)

target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Widgets)

set(PROJECT_TWO_FILECODER FileCoder)
add_executable(${PROJECT_TWO_FILECODER}
        src/FileCoder/main.cpp
        src/FileCoder/daunit.cpp
        src/FileCoder/daunit.h
        src/FileCoder/filecoder.cpp
        src/FileCoder/filecoder.h
        src/FileCoder/dadecoder.cpp
        src/FileCoder/dadecoder.h
        src/FileCoder/daencoder.cpp
        src/FileCoder/daencoder.h)

#target_link_libraries(${PROJECT_TWO_FILECODER} Qt${QT_VERSION_MAJOR}::Widgets)

set(PROJECT_KkGis KkGis)
include_directories(KkGis)
aux_source_directory(KkGis KkGis)
add_executable(${PROJECT_KkGis}
        ${KkGis})

target_link_libraries(${PROJECT_KkGis} Qt${QT_VERSION_MAJOR}::Widgets)

set(PROJECT_MmGis MmGis)
include_directories(MmGis)
aux_source_directory(MmGis MmGis)
add_executable(${PROJECT_MmGis}
        ${MmGis})

target_link_libraries(${PROJECT_MmGis} Qt${QT_VERSION_MAJOR}::Widgets)