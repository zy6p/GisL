qt5_wrap_ui(GISL_UI_HDRS
        mainwindow.ui
        chooserasterrgb.ui
        imgviewwidget.ui
        analysisform.ui
        )
add_custom_target(ui ALL DEPENDS ${GISL_UI_HDRS})
