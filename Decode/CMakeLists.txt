cmake_minimum_required(VERSION 3.5)
project(Decode)

set(QT_VERSION_MAJOR 5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_PREFIX_PATH C:/ProgramXXX/Qt/5.15.1/msvc2019_64/)
    set(QT5_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5/)
    set(Qt5Core_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Core/)
    set(Qt5Gui_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Gui/)
    set(Qt5Widgets_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5Widgets/)
    set(Qt5_DIR C:/ProgramXXX/Qt/5.15.1/mingw81_64/lib/cmake/Qt5/)

    #-GNinja
    #-DCMAKE_BUILD_TYPE:String=Debug
    #-DQT_QMAKE_EXECUTABLE:STRING=%{Qt:qmakeExecutable}
    #-DCMAKE_PREFIX_PATH:STRING=%{Qt:QT_INSTALL_PREFIX}
    #-DCMAKE_C_COMPILER:STRING=%{Compiler:Executable:C}
    #-DCMAKE_CXX_COMPILER:STRING=%{Compiler:Executable:Cxx}
endif()

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_ONE Decode)
add_executable(${PROJECT_ONE}
        main.cpp
        daunit.cpp
        daunit.h
        dadecoder.cpp
        dadecoder.h)
target_link_libraries(${PROJECT_ONE} Qt${QT_VERSION_MAJOR}::Widgets)

set(PROJECT_TWO DecodeGui)
add_executable(${PROJECT_TWO}
        decodegui.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        daunit.cpp
        daunit.h
        dadecoder.cpp
        dadecoder.h)
target_link_libraries(${PROJECT_TWO} Qt${QT_VERSION_MAJOR}::Widgets)
