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

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "painter/painterfactory.h"
#include "../core/vectorprovider.h"
#include "../utils/gislobject.h"


class GlCanvas : public QOpenGLWidget, protected QOpenGLFunctions, public GisL::PainterFactory {
Q_OBJECT
public:
    explicit GlCanvas( QWidget *parent );

    ~GlCanvas( ) override;

    using QOpenGLWidget::QOpenGLWidget;

    float nearPlane = -100.0f;
    float farPlane = 100.0f;
    QMatrix4x4 finalMatrix;
    QMatrix4x4 scaleMatrix;

//    void getEnvelope( GisL::Rectangle &rectangle ) override;

    void drawPoint( GisL::ExchangePointXY &p ) override;

    void drawLine( GisL::ExchangeLine &p ) override;

    void getEnvelope( GisL::Rectangle &rectangle ) override;

    void drawPolygon( GisL::ExchangePolygon &p ) override;

    void drawMultiPolygon( GisL::ExchangePolygon **p, int count ) override;

    void drawLinearRing( GisL::ExchangeLinearRing *p ) override;

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

    QPoint lastPos;
    std::vector<GisL::ExchangeLinearRing *> mLinearRing;
    int mLinearRingCount;

    std::vector<QOpenGLVertexArrayObject *> m_vao_lineLoop;
    std::vector<QOpenGLBuffer *> m_vbo_lineLoop;
    QOpenGLShaderProgram *m_program;

//    QOpenGLVertexArrayObject *vao;
//    QOpenGLBuffer *vbo;
//    QOpenGLShaderProgram *program;
};


#endif //GISL_GLCANVAS_H
