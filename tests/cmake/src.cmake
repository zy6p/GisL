##set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)
#
#add_executable(GisL
#        main.cpp mainwindow.cpp mainwindow.h
#        ${GISL_CODECVT_SUBDIR} ${GISL_GIS_SUBDIR} ${GISL_PLOT_SUBDIR} ${GISL_UTILS_SUBDIR}
##        ${GISL_CODECVT_SRCS} ${GISL_CODECVT_HDRS}
##        ${GISL_GIS_SRCS} ${GISL_GIS_HDRS}
##        ${GISL_PLOT_SRCS} ${GISL_PLOT_HDRS}
##        ${GISL_UTILS_SRCS} ${GISL_UTILS_HDRS}
#        )
#
##add_subdirectory(codecvt)
##add_subdirectory(gis)
##add_subdirectory(utils)
##add_subdirectory(plot)
#
#target_link_libraries(GisL
##        PRIVATE
##        codecvt
##        gis
##        utils
##        plot
#        PUBLIC
#        Qt${QT_VERSION_MAJOR}::Widgets
#        GDAL
#        OpenGL GLUT
#        )
#
##target_link_libraries(GisL )
##target_link_libraries(GisL GDAL)
##target_link_libraries(GisL )
#
