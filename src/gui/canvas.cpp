/*!
 * @file cancas.cpp.cc
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief
 * @details 
 * @verbatim
 *
 */

//#include <QtOpenGL>

#include "canvas.h"


namespace GisL {
    Canvas::Canvas( QOpenGLWidget &poQOpenGlWidget ) {
        pmQOpenGlWidget = &poQOpenGlWidget;



    }

    void Canvas::initializeGL( ) {

    }

    void Canvas::paintGL( ) {

    }

    void Canvas::resizeGL( int w, int h ) {

    }


}