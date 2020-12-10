cmake_minimum_required(VERSION 3.17.1)

project(GisL LANGUAGES CXX)
set(QT_VERSION_MAJOR 5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(CMAKE_PREFIX_PATH C:/ProgramXXX/Qt/Tools/mingw810_64/)
    set(QT5_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5/)
    set(Qt5Core_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Core/)
    set(Qt5Gui_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Gui/)
    set(Qt5Widgets_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Widgets/)
    set(Qt5_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5/)

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
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        FileCoder/daunit.cpp FileCoder/daunit.h FileCoder/filecoder.cpp FileCoder/filecoder.h FileCoder/dadecoder.cpp FileCoder/dadecoder.h FileCoder/daencoder.cpp FileCoder/daencoder.h)

target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Widgets)

set(PROJECT_TWO_FILECODER FileCoder)
add_executable(${PROJECT_TWO_FILECODER}
        FileCoder/main.cpp
        FileCoder/daunit.cpp
        FileCoder/daunit.h
        FileCoder/filecoder.cpp
        FileCoder/filecoder.h
        FileCoder/dadecoder.cpp
        FileCoder/dadecoder.h
        FileCoder/daencoder.cpp
        FileCoder/daencoder.h)

#target_link_libraries(${PROJECT_TWO_FILECODER} Qt${QT_VERSION_MAJOR}::Widgets)
