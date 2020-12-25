/*!
 * @file cancas.h
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief map canvas
 * @details 
 * @verbatim
 *
 */

#ifndef GISL_CANVAS_H
#define GISL_CANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLContext>

//#include ""
#include "../utils/gislobject.h"


namespace GisL {
    class Canvas : public GisLObject {
    public:
        explicit Canvas(QOpenGLWidget &poQOpenGlWidget);


    private:
        QOpenGLWidget *pmQOpenGlWidget;

        void initializeGL();

        void paintGL();

        void resizeGL(int w, int h);

    };
}

#endif //GISL_CANVAS_H
