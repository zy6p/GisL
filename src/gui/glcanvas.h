/*!
 * @file glcanvas.h
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief map canvas
 * @details
 *
 */

#ifndef GISL_GLCANVAS_H
#define GISL_GLCANVAS_H

//#include "ui_mainwindow.h"

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <vector>

#include "../core/vectorprovider.h"
#include "../utils/gislobject.h"


class GlCanvas : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT
public:
    explicit GlCanvas( QWidget *parent );

    ~GlCanvas( ) override;

    using QOpenGLWidget::QOpenGLWidget;

signals:

    void clicked( );

protected:

    void initializeGL( ) override;

    void resizeGL( int w, int h ) override;

    void paintGL( ) override;

    void mousePressEvent( QMouseEvent *event ) override;

    void mouseMoveEvent( QMouseEvent *event ) override;

    void mouseReleaseEvent( QMouseEvent *event ) override;

    void mouseDoubleClickEvent( QMouseEvent *event ) override;

    void wheelEvent( QWheelEvent *event ) override;

private:

    QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer *m_vbo;
    QOpenGLShaderProgram *m_program;
};


#endif //GISL_GLCANVAS_H
