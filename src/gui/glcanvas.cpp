/*!
 * @file glcanvas.cpp
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief
 * @details
 *
 */

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_INCOLOR_ATTRIBUTE 1

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QWheelEvent>

#include "../core/vectorprovider.h"
#include "glcanvas.h"
#include "../utils/ptroperate.h"

GlCanvas::GlCanvas( QWidget *parent ) :
        QOpenGLWidget( parent ), m_program( nullptr ) {

    mLinearRingCount = 0;
    setEnabled( true );
}

static const char *VERTEX_SHADER_CODE =
        "#version 330 core\n"
        "layout(location = 0) in vec2 inVertex;\n"
        "layout(location = 1) in vec2 inColor;\n"
        "uniform mediump mat4 matrix;\n"
        "out vec2 ourColor;\n"
        "void main() {\n"
        "  ourColor = inColor;\n"
        //        "  gl_Position = vec4(inVertex, 0.0f, 1.0f);\n"
        "  gl_Position = matrix * vec4(inVertex, 0.0f, 1.0f);\n"
        "}\n";

static const char *FRAGMENT_SHADER_CODE =
        "#version 330 core\n"
        "in vec2 ourColor;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
        "}\n";

void GlCanvas::initializeGL( ) {
    this->initializeOpenGLFunctions();
    this->glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

    auto *vshader = new QOpenGLShader( QOpenGLShader::Vertex, this );
    const char *vsrc =
            "#version 330 core\n"
            "attribute highp vec4 vertex;\n"
            "attribute mediump vec4 texCoord;\n"
            "varying mediump vec4 texc;\n"
            "uniform mediump mat4 matrix;\n"
            "void main(void)\n"
            "{\n"
            "    gl_Position = matrix * vertex;\n"
            "    texc = texCoord;\n"
            "}\n";
    vshader->compileSourceCode( VERTEX_SHADER_CODE );

    auto *fshader = new QOpenGLShader( QOpenGLShader::Fragment, this );
    const char *fsrc =
            "#version 330 core\n"
            "uniform sampler2D texture;\n"
            "varying mediump vec4 texc;\n"
            "void main(void)\n"
            "{\n"
            "    gl_FragColor = texture2D(texture, texc.st);\n"
            "}\n";
    fshader->compileSourceCode( FRAGMENT_SHADER_CODE );

    m_program = new QOpenGLShaderProgram;
    m_program->addShader( vshader );
    m_program->addShader( fshader );
    m_program->bindAttributeLocation( "inVertex", PROGRAM_VERTEX_ATTRIBUTE );
    m_program->bindAttributeLocation( "inColor", PROGRAM_INCOLOR_ATTRIBUTE );
    m_program->link();
    m_program->bind();

}


void GlCanvas::resizeGL( int w, int h ) {
    this->glViewport( 0, 22, w, h );
}

void GlCanvas::paintGL( ) {
//    this->context()->functions();
    this->glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    this->glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

    m_program->setUniformValue( "matrix", finalMatrix );

    for ( int i = 0; i < mLinearRingCount; ++i ) {
        m_vbo_lineLoop[i]->bind();
        m_vao_lineLoop[i]->bind();
        m_program->enableAttributeArray( PROGRAM_VERTEX_ATTRIBUTE );
        m_program->enableAttributeArray( PROGRAM_INCOLOR_ATTRIBUTE );
        m_program->setAttributeBuffer( PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 2, 2 * sizeof( GLfloat ));
        m_program->setAttributeBuffer( PROGRAM_INCOLOR_ATTRIBUTE, GL_FLOAT, 0, 2, 2 * sizeof( GLfloat ));

        glDrawArrays( GL_LINE_LOOP, 0, mLinearRing[i]->posCount );

        m_vao_lineLoop[i]->release();
        m_vbo_lineLoop[i]->release();
    }
}

GlCanvas::~GlCanvas( ) {
    makeCurrent();

    m_vao_lineLoop[0]->destroy();
    m_vbo_lineLoop[0]->destroy();
    delete m_program;

    doneCurrent();
}

void GlCanvas::mousePressEvent( QMouseEvent *event ) {
    QWidget::mousePressEvent( event );
    lastPos = event->pos();
}

void GlCanvas::mouseMoveEvent( QMouseEvent *event ) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    finalMatrix.translate( 100 * dx, 100 * -dy );
    lastPos = event->pos();
    update();
}

void GlCanvas::mouseReleaseEvent( QMouseEvent *event ) {
    QWidget::mouseReleaseEvent( event );

}

void GlCanvas::mouseDoubleClickEvent( QMouseEvent *event ) {
    QWidget::mouseDoubleClickEvent( event );
}

void GlCanvas::wheelEvent( QWheelEvent *event ) {
//    QMatrix4x4 camera;
//    QVector3D my_eye;
//    my_eye.setX(0);
//    my_eye.setY(0);
//    my_eye.setZ(0.5);
//    camera.lookAt(my_eye, QVector3D(0, 0, 0), QVector3D(0,1,0));

    if ( event->delta() > 0 ) {
        finalMatrix.scale( 1.2 );
    } else {
        finalMatrix.scale( 0.8 );
    }
    update();
}

void GlCanvas::drawPoint( GisL::ExchangePointXY &p ) {

}

void GlCanvas::drawLine( GisL::ExchangeLine &p ) {

}

void GlCanvas::drawPolygon( GisL::ExchangePolygon &p ) {

}

void GlCanvas::drawMultiPolygon( GisL::ExchangePolygon **p, int count ) {

}

void GlCanvas::drawLinearRing( GisL::ExchangeLinearRing *p ) {
    makeCurrent();
    mLinearRing.push_back( p );
    m_vao_lineLoop.push_back( new QOpenGLVertexArrayObject( this ));
    m_vbo_lineLoop.push_back( new QOpenGLBuffer( QOpenGLBuffer::Type::VertexBuffer ));
    m_vao_lineLoop[mLinearRingCount]->create();
    m_vao_lineLoop[mLinearRingCount]->bind();
    m_vbo_lineLoop[mLinearRingCount]->create();
    m_vbo_lineLoop[mLinearRingCount]->bind();

    m_vbo_lineLoop[mLinearRingCount]->allocate( p->posVector.constData(), p->posVector.count() * sizeof( GLfloat ));
    m_vao_lineLoop[mLinearRingCount]->release();
    m_vbo_lineLoop[mLinearRingCount]->release();
    mLinearRingCount++;
    doneCurrent();
    update();
}

void GlCanvas::getEnvelope( GisL::Rectangle &rectangle ) {
    PainterFactory::getEnvelope( rectangle );
    if ( nullptr == pmEnvelope ) {
        finalMatrix.setToIdentity();
    } else {
        float dx = pmEnvelope->maxX - pmEnvelope->minX;
        float dy = pmEnvelope->maxY - pmEnvelope->minY;
        if ( dy > dx ) {
            finalMatrix.ortho( pmEnvelope->minX - ( dy - dx ) / 2, pmEnvelope->maxX + ( dy - dx ) / 2, pmEnvelope->minY,
                               pmEnvelope->maxY, -1.0f, 1.0f );
        } else {
            finalMatrix.ortho( pmEnvelope->minX, pmEnvelope->maxX, pmEnvelope->minY - ( dx - dy ) / 2,
                               pmEnvelope->maxY + ( dx - dy ) / 2, -1.0f, 1.0f );

        }
//        finalMatrix.ortho( pmEnvelope->minX, pmEnvelope->maxX, pmEnvelope->minY, pmEnvelope->maxY, -1.0f, 1.0f );
    }
}

