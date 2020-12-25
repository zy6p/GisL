/*!
 * @file canvas.cpp
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief
 * @details
 *
 */

//#include <QtOpenGL>

#include "canvas.h"


namespace GisL {
    Canvas::Canvas( Ui_MainWindow &poUi ) {
        pmUi = &poUi;
        pmQOpenGlWidget = pmUi->openGLWidget;


    }

    void Canvas::initializeGL( ) {

    }

    void Canvas::paintGL( ) {

    }

    void Canvas::resizeGL( int w, int h ) {

    }


}