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

#include "ui_mainwindow.h"

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "../utils/gislobject.h"


namespace GisL {
    class GlCanvas : public QOpenGLWidget, GisLObject, protected QOpenGLFunctions {
    Q_OBJECT
    public:
        explicit GlCanvas( Ui_MainWindow &poUi );

        ~GlCanvas( ) override;

        using QOpenGLWidget::QOpenGLWidget;

        QSize minimumSizeHint( ) const override;

        QSize sizeHint( ) const override;

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
        Ui_MainWindow *pmUi;

        void makeObject( );

        QPoint lastPos;
        int xRot = 0;
        int yRot = 0;
        int zRot = 0;
        QOpenGLTexture *textures[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
        QOpenGLShaderProgram *program = nullptr;
        QOpenGLBuffer vbo;

        QOpenGLVertexArrayObject m_vao;
        QOpenGLBuffer m_vbo;

        QOpenGLShaderProgram *m_program;
        QOpenGLShader *m_shader;
        QOpenGLTexture *m_texture;
    };
}

#endif //GISL_GLCANVAS_H
