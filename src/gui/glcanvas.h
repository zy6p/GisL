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
#include <QMatrix4x4>
#include <QLabel>

#include "painter/painterfactory.h"
#include "../core/vectorprovider.h"


class GlCanvas : public QOpenGLWidget, protected QOpenGLFunctions, public GisL::PainterFactory {
Q_OBJECT
public:
    explicit GlCanvas( QWidget *parent );

    ~GlCanvas( ) override;

    using QOpenGLWidget::QOpenGLWidget;

//    void getEnvelope( GisL::Rectangle &rectangle ) override;

    void drawPoint( GisL::ExchangePointXY &p ) override;

    void drawLine( GisL::ExchangeLine &p ) override;

    void getEnvelope( GisL::Rectangle &rectangle ) override;

    void getLayer( GisL::VectorLayer &layer );

    void setRandSld( ) override;

    void drawPolygon( GisL::ExchangePolygon &p ) override;

    void drawMultiPolygon( GisL::ExchangePolygon **p, int count ) override;

    void drawLinearRing( GisL::ExchangeLinearRing *p, const std::string &featureName ) override;

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

//    void paintEvent( QPaintEvent *e ) override;

private:

    qreal translateX;
    qreal translateY;
    qreal scaleX;
    qreal scaleY;
    qreal scale;
    qreal rotateAngle;

    QMatrix4x4 projMatrix;
    QMatrix4x4 cameraMatrix;
    QMatrix4x4 scaleMatrix;

    QPoint lastPos;
    std::vector<GisL::ExchangeLinearRing *> mLinearRing;
    std::vector<std::string> mLinearRingName;
    int mLinearRingCount;

    QVector<GisL::VectorLayer *> mLayer;
    QVector<QLabel *> mLayerLabel;

    std::vector<QOpenGLVertexArrayObject *> m_vao_lineLoop;
    std::vector<QOpenGLBuffer *> m_vbo_lineLoop;
    QOpenGLShaderProgram *m_program;

    //    QOpenGLVertexArrayObject *vao;
//    QOpenGLBuffer *vbo;
//    QOpenGLShaderProgram *program;
    void calProjMatrix( );

    void drawLabel( );
};


#endif //GISL_GLCANVAS_H
