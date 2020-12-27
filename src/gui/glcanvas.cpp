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

#include "glcanvas.h"
#include "../utils/ptroperate.h"

namespace GisL {
    GlCanvas::GlCanvas( Ui_MainWindow &poUi ) {
        pmUi = &poUi;
        setAutoFillBackground( false );

    }

    void GlCanvas::initializeGL( ) {
        initializeOpenGLFunctions();
//        makeObject();
        glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );


    }

    void GlCanvas::resizeGL( int w, int h ) {

    }

    void GlCanvas::paintGL( ) {
        glClear( GL_COLOR_BUFFER_BIT );
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

    void GlCanvas::makeObject( ) {
        static const int coords[6][4][3] = {
                {{ +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 }},
                {{ +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 }},
                {{ +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 }},
                {{ -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 }},
                {{ +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 }},
                {{ -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 }}
        };

        for ( int j = 0; j < 6; ++j )
            textures[j] = new QOpenGLTexture( QImage( QString( ":/images/side%1.png" ).arg( j + 1 )).mirrored());

        QVector<GLfloat> vertData;
        for ( const auto &coord : coords ) {
            for ( int j = 0; j < 4; ++j ) {
                // vertex position
                vertData.append( 0.2 * coord[j][0] );
                vertData.append( 0.2 * coord[j][1] );
                vertData.append( 0.2 * coord[j][2] );
                // texture coordinate
                vertData.append( j == 0 || j == 3 );
                vertData.append( j == 0 || j == 1 );
            }
        }

        vbo.create();
        vbo.bind();
        vbo.allocate( vertData.constData(), vertData.count() * sizeof( GLfloat ));
    }

    void GlCanvas::wheelEvent( QWheelEvent *event ) {
        QWidget::wheelEvent( event );
    }


}
