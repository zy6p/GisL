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