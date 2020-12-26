/*!
 * @file canvas.h
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief map canvas
 * @details
 *
 */

#ifndef GISL_CANVAS_H
#define GISL_CANVAS_H

#include "ui_mainwindow.h"

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLContext>

#include "../utils/gislobject.h"


namespace GisL {
    class Canvas : public GisLObject {
    public:
        explicit Canvas( Ui_MainWindow &poUi );


    private:
        Ui_MainWindow *pmUi;
        QOpenGLWidget *pmQOpenGlWidget;

        void initializeGL( );

        void paintGL( );

        void resizeGL( int w, int h );

    };
}

#endif //GISL_CANVAS_H
