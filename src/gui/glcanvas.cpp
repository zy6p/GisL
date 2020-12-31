/*!
 * @file glcanvas.cpp
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief
 * @details
 *
 */

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "../core/vector.h"
#include "glcanvas.h"
#include "../utils/ptroperate.h"

GlCanvas::GlCanvas( QWidget *parent ) :
        QOpenGLWidget( parent ), m_vbo( nullptr ), m_vao( nullptr ), m_program( nullptr ) {
    this->pQWidget = parent;
    setAutoFillBackground( false );
    pmVector = new GisL::Vector *[100];
    vectorCount = 0;
}

void GlCanvas::importVector( GisL::Vector &vector ) {
    pmVector[vectorCount] = &vector;
    vectorCount++;
}

void GlCanvas::initializeGL( ) {
    this->initializeOpenGLFunctions();
//        makeObject();
//        glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );


}

void GlCanvas::resizeGL( int w, int h ) {
    this->glViewport( 0, 22, w, h );
}

void GlCanvas::paintGL( ) {
    this->glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    this->glClear( GL_COLOR_BUFFER_BIT );
    update();
}

GlCanvas::~GlCanvas( ) {
    makeCurrent();


    doneCurrent();
}

QSize GlCanvas::minimumSizeHint( ) const {
    return { 50, 50 };
}

QSize GlCanvas::sizeHint( ) const {
    return { 800, 800 };
}

void GlCanvas::makeObject( ) {

}

void GlCanvas::mousePressEvent( QMouseEvent *event ) {
    QWidget::mousePressEvent( event );
}

void GlCanvas::mouseMoveEvent( QMouseEvent *event ) {
    QWidget::mouseMoveEvent( event );
}

void GlCanvas::mouseReleaseEvent( QMouseEvent *event ) {
    QWidget::mouseReleaseEvent( event );

}

void GlCanvas::mouseDoubleClickEvent( QMouseEvent *event ) {
    QWidget::mouseDoubleClickEvent( event );
}

void GlCanvas::wheelEvent( QWheelEvent *event ) {
    QWidget::wheelEvent( event );
}



