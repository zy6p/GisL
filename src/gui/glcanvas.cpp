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

#include "../core/vectorprovider.h"
#include "glcanvas.h"
#include "../utils/ptroperate.h"

GlCanvas::GlCanvas( QWidget *parent ) :
        QOpenGLWidget( parent ), m_vbo( nullptr ), m_vao( nullptr ), m_program( nullptr ) {

//    setAutoFillBackground( false );

}

static const char *VERTEX_SHADER_CODE =
        "#version 330 \n"
        "layout(location = 0) in vec3 posVertex;\n"
        "void main() {\n"
        "  gl_Position = vec4(posVertex, 1.0f);\n"
        "}\n";

static const char *FRAGMENT_SHADER_CODE =
        "#version 330\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "  fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
        "}\n";

void glVertexAttribPointer(
        GLuint index,
        GLint size,
        GLenum type,
        GLboolean normalized,
        GLsizei stride,
        const void *pointer
);

void GlCanvas::initializeGL( ) {
    this->initializeOpenGLFunctions();
//    this->glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode( QOpenGLShader::Vertex, VERTEX_SHADER_CODE );
    m_program->addShaderFromSourceCode( QOpenGLShader::Fragment, FRAGMENT_SHADER_CODE );
    if ( m_program->link()) {
        qDebug( "success" );
    } else {
        qDebug( "fail" );
    }

    m_vao = new QOpenGLVertexArrayObject();
    m_vbo = new QOpenGLBuffer( QOpenGLBuffer::Type::VertexBuffer );
    m_vao->create();
    m_vao->bind();

    static const GLfloat VERTEX_DATA[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
    };

    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate( VERTEX_DATA, 3 * 3 * sizeof( GLfloat ));

    this->context()->functions();
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), nullptr );

    m_vbo->release();
    m_vao->release();
}


void GlCanvas::resizeGL( int w, int h ) {
    this->glViewport( 0, 22, w, h );
}

void glDrawArrays( GLenum mode,
                   GLint fist,
                   GLsizei count );

void GlCanvas::paintGL( ) {
    this->context()->functions();
    this->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    this->glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

    m_vao->bind();
    m_program->bind();
    glDrawArrays( GL_TRIANGLES, 0, 3 );

    m_program->release();
    m_vao->release();
//    update();
}

GlCanvas::~GlCanvas( ) {
    makeCurrent();


    doneCurrent();
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



