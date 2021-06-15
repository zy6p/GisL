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

#include <QLabel>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QPaintEvent>
#include <QPainter>
#include <QWheelEvent>

#include "utils/ptroperate.h"
#include "core/provider/vectorprovider.h"
#include "glcanvas.h"
#include "render/multipolygonfs.h"
#include "render/multipolygonvs.h"
#include "symbolizer/polygonsymbolizer.h"

GlCanvas::GlCanvas(QWidget* parent)
    : QOpenGLWidget(parent), m_program(nullptr) {

    mLinearRingCount = 0;
    scaleMatrix.setToIdentity();
    setEnabled(true);
}

void GlCanvas::initializeGL() {
    //  pmPixmap = std::make_unique<QPixmap>(QPixmap{"/home/km/dev/gisl/tests/data/rs/1/combination/gaojing_subset.tif.png"});
    this->initializeOpenGLFunctions();
    this->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    auto* vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vshader->compileSourceCode(MultiPolygonVS.c_str());

    auto* fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fshader->compileSourceCode(MultiPolygonFS.c_str());

    m_program = new QOpenGLShaderProgram;
    m_program->addShader(vshader);
    m_program->addShader(fshader);
    m_program->bindAttributeLocation("inVertex", PROGRAM_VERTEX_ATTRIBUTE);
    //    m_program->bindAttributeLocation( "inColor", PROGRAM_INCOLOR_ATTRIBUTE
    //    );
    m_program->link();
    m_program->bind();

    //    auto *dada = new QLabel( "hrloosd", this );
    //    dada->move( 22, 45 );
    //    for ( int i = 0; i < 11; ++i ) {
    //        mLayerLabel[i] = new QLabel("dasdasd", this );
    //        mLayerLabel[i]->setText("dasdasd");
    //        mLayerLabel[i]->move(i * 10, i * 10);
    //    }
}

void GlCanvas::resizeGL(int w, int h) {
    this->glViewport(0, 22, w, h);
    //    if ( nullptr == pmEnvelope ) {
    //        projMatrix.setToIdentity();
    //    } else {
    //        calProjMatrix();
    //    }
    update();
}

void GlCanvas::paintGL() {
    //    this->context()->functions();
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    m_program->setUniformValue("matrix", projMatrix * scaleMatrix);

    makeCurrent();
    for (int i = 0; i < mLinearRingCount; ++i) {
        m_vbo_lineLoop[i]->bind();
        m_vao_lineLoop[i]->bind();
        m_program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
        //        m_program->enableAttributeArray( PROGRAM_INCOLOR_ATTRIBUTE );
        m_program->setAttributeBuffer(
            PROGRAM_VERTEX_ATTRIBUTE,
            GL_FLOAT,
            0,
            2,
            2 * sizeof(GLfloat));
        //        m_program->setAttributeBuffer( PROGRAM_INCOLOR_ATTRIBUTE,
        //        GL_FLOAT, 0, 2, 2 * sizeof( GLfloat )); QColor fillColor =
        //        pmSld->getSymbolizerMap().find( mLinearRingName[i]
        //        )->second->getDefColor(
        //                "polygonFillColor" );

        //        GLfloat color[] = {(GLfloat )fillColor.redF(), (GLfloat
        //        )fillColor.greenF(), (GLfloat )fillColor.blueF()}; qDebug("%f, %f,
        //        %f", fillColor.redF(), fillColor.blueF(), fillColor.greenF());
        m_program->setUniformValue("inColor", QColor(Qt::black));

        glDrawArrays(GL_LINE_LOOP, 0, mLinearRing[i]->posCount);

        m_vao_lineLoop[i]->release();
        m_vbo_lineLoop[i]->release();
    }
    doneCurrent();

    QPainter painter(this);

    if (pmPixmap != nullptr) {
        painter.drawPixmap(0, 0, *pmPixmap);
    }

    for (int i = 0; i < mLinearRingCount; ++i) {
        //        for ( int j = 0; j < mLinearRing[i]->posCount; ++j ) {
        //            mLinearRing[i]->qPolygon[j].setX()
        //        }
        painter.setPen(pmSld->getSymbolizerMap()
                       .find(mLinearRingName[i])
                       ->second->getDefColor("polygonFillColor"));
        painter.setBrush(pmSld->getSymbolizerMap()
                         .find(mLinearRingName[i])
                         ->second->getDefColor("polygonFillColor"));

        //        painter.drawRect( pmEnvelope->minX, pmEnvelope->minY,
        //        pmEnvelope->maxX - pmEnvelope->minX,
        //                          pmEnvelope->maxY - pmEnvelope->minY );
        //        painter.drawLine( 0, 0, 500 * i, 1000 * i * i );
        painter.drawPolygon(mLinearRing[i]->qPolygon);
        //        qDebug( "%f, %f", mLinearRing[i]->qPolygon[0].x(),
        //        mLinearRing[i]->qPolygon[0].y());
        //        painter.setWorldMatrix(projMatrix);
        //        mLinearRing[i]->qPolygon.
        //        mLinearRing[i]->qPolygon.translate(translateX, translateY);
    }
    if (nullptr == pmEnvelope) {
        projMatrix.setToIdentity();
    } else {
        //        painter.translate(pmEnvelope->center());
    }

    painter.scale(scale, -scale);
    painter.translate(translateX, -translateY);
    //    painter.scale(3, 3);
    //    painter.translate(100, 100);

    painter.setPen(Qt::black);
    QFont font;
    //    font.setBold( true );
    //    font.setPixelSize( 2000 );
    font.setPointSize(1000);
    painter.setFont(font);
    //    painter.rotate(90);
    for (auto pLayer : mLayer) {
        for (int i = 0; i < pLayer->getFeatureCount(); ++i) {
            auto labelPosF = pLayer->getFeature()[i]->boundary()->center();
            //            labelPosF = projMatrix.map(scaleMatrix.map( labelPosF ));
            //            labelPosF.setX(( labelPosF.x() + 1 ) *
            //            this->size().width()); labelPosF.setY(( 1 - labelPosF.y() )
            //            * this->size().height());
            painter.drawText(
                labelPosF.x(),
                labelPosF.y(),
                QString((pLayer->getFeature()[i]
                         ->getFieldAsString(pmSld->getPropertyName())
                         .c_str())));

            //            painter.drawText(
            //            pLayer->getFeature()[i]->boundary()->getQRectF(), 0,
            //                              QString((
            //                              pLayer->getFeature()[i]->getFieldAsString(
            //                              pmSld->getPropertyName()).c_str())));
            //            qDebug( "%s %f, %f", (
            //            pLayer->getFeature()[i]->getFieldAsString(
            //            pmSld->getPropertyName()).c_str()),
            //                    labelPosF.x(), labelPosF.y());
        }
    }
    //    painter.rotate(180);
    //    for (  )
    //    drawLabel();
}

// void GlCanvas::paintEvent( QPaintEvent *e ) {
//     QPainter painter( this);
//
//     painter.setPen( Qt::black );
//     for ( auto pLayer : mLayer ) {
//         for ( int i = 0; i < pLayer->getFeatureCount(); ++i ) {
//             auto labelPosF = projMatrix.map(
//             pLayer->getFeature()[i]->boundary()->center()); labelPosF =
//             scaleMatrix.map( labelPosF ); labelPosF.setX(( labelPosF.x() + 1
//             ) * this->size().width()); labelPosF.setY(( labelPosF.y() + 1 ) *
//             this->size().height()); painter.drawText( labelPosF.toPoint(),
//                               QString((
//                               pLayer->getFeature()[i]->getFieldAsString(
//                               pmSld->getPropertyName()).c_str())));
//         }
//     }
// }

void GlCanvas::drawLabel() {

    for (auto layer : mLayer) {
        for (int i = 0; i < layer->getFeatureCount(); ++i) {
            auto labelPosF =
                projMatrix.map(layer->getFeature()[i]->boundary()->center());
            labelPosF = scaleMatrix.map(labelPosF);
            labelPosF.setX((labelPosF.x() + 1) * this->size().width());
            labelPosF.setY((labelPosF.y() + 1) * this->size().height());
            //            mLayerLabel.push_back(
            //            auto *q =
            mLayerLabel[i]->setText(
                QString((layer->getFeature()[i]
                         ->getFieldAsString(pmSld->getPropertyName())
                         .c_str()))),
                                //            q->move(labelPosF.toPoint());
                                mLayerLabel[i]->move(labelPosF.toPoint());
            //            mLayerLabel[i].set
        }
    }

    //    auto *dada = new QLabel("hrloosd", this);
    //    dada->move(22, 45);
}

GlCanvas::~GlCanvas() {
    makeCurrent();

    for (int i = 0; i < mLinearRingCount; ++i) {
        m_vao_lineLoop[i]->destroy();
        m_vbo_lineLoop[i]->destroy();
    }
    delete m_program;

    doneCurrent();
}

void GlCanvas::mousePressEvent(QMouseEvent* event) {
    QWidget::mousePressEvent(event);
    lastPos = event->pos();
}

void GlCanvas::mouseMoveEvent(QMouseEvent* event) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    projMatrix.translate((float)(100 * dx), (float)(100 * -dy));
    translateX += dx / scale;
    translateY += dy / scale;
    lastPos = event->pos();
    update();
}

void GlCanvas::mouseReleaseEvent(QMouseEvent* event) {
    QWidget::mouseReleaseEvent(event);
}

void GlCanvas::mouseDoubleClickEvent(QMouseEvent* event) {
    QWidget::mouseDoubleClickEvent(event);
}

void GlCanvas::wheelEvent(QWheelEvent* event) {
    //    QMatrix4x4 camera;
    //    QVector3D my_eye;
    //    my_eye.setX(0);
    //    my_eye.setY(0);
    //    my_eye.setZ(0.5);
    //    camera.lookAt(my_eye, QVector3D(0, 0, 0), QVector3D(0,1,0));

    if (event->delta() > 0) {
        scaleMatrix.scale(1.2);
        scale = scale * 1.2;
    } else {
        scaleMatrix.scale(0.8);
        scale = scale * 0.8;
    }
    update();
}

void GlCanvas::drawPoint(gisl::ExchangePointXY& p) {}

void GlCanvas::drawLine(gisl::ExchangeLine& p) {}

void GlCanvas::drawPolygon(gisl::ExchangePolygon& p) {}

void GlCanvas::drawMultiPolygon(gisl::ExchangePolygon** p, int count) {}

void GlCanvas::drawLinearRing(
    gisl::ExchangeLinearRing* p,
    const std::string& featureName) {
    mLinearRingName.push_back(featureName);
    makeCurrent();
    mLinearRing.push_back(p);
    m_vao_lineLoop.push_back(new QOpenGLVertexArrayObject(this));
    m_vbo_lineLoop.push_back(
        new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer));
    m_vao_lineLoop[mLinearRingCount]->create();
    m_vao_lineLoop[mLinearRingCount]->bind();
    m_vbo_lineLoop[mLinearRingCount]->create();
    m_vbo_lineLoop[mLinearRingCount]->bind();

    m_vbo_lineLoop[mLinearRingCount]->allocate(
        p->posVector.constData(),
        p->posCount * 2 * sizeof(GLfloat));
    m_vao_lineLoop[mLinearRingCount]->release();
    m_vbo_lineLoop[mLinearRingCount]->release();
    mLinearRingCount++;
    doneCurrent();
    update();
}

void GlCanvas::getEnvelope(gisl::Rectangle& rectangle) {
    PainterFactory::getEnvelope(rectangle);
    //    this->size()
    if (nullptr == pmEnvelope) {
        projMatrix.setToIdentity();
    } else {
        calProjMatrix();
    }

    // QPainter
    scaleX = (double)this->size().width() / (pmEnvelope->maxX - pmEnvelope->minX);
    scaleY =
        (double)this->size().height() / (pmEnvelope->maxY - pmEnvelope->minY);
    if (scaleX > scaleY) {
        scale = scaleY;
    } else {
        scale = scaleX;
    }

    //    translateX = -pmEnvelope->minX * scale + ( double ) this->size().width()
    //    / 2; translateY = -pmEnvelope->minY * scale + ( double )
    //    this->size().height() / 2;
    translateX = -pmEnvelope->minX; //+ ( double ) this->size().width() / 2;
    translateY = pmEnvelope->maxY;  // - ( double ) this->size().height() / 2;
}

void GlCanvas::calProjMatrix() {
    float widgetWidth = pmEnvelope->maxX - pmEnvelope->minX;
    float widgetHeight = pmEnvelope->maxY - pmEnvelope->minY;
    float widthRatio = widgetHeight / (float)size().width();
    float heightRatio = widgetHeight / (float)size().height();
    if (widthRatio > heightRatio) {
        projMatrix.ortho(
            pmEnvelope->minX - (widgetHeight - widgetWidth) / 2,
            pmEnvelope->maxX + (widgetHeight - widgetWidth) / 2,
            pmEnvelope->minY,
            pmEnvelope->maxY,
            -1.0f,
            1.0f);
    } else {
        projMatrix.ortho(
            pmEnvelope->minX,
            pmEnvelope->maxX,
            pmEnvelope->minY - (widgetWidth - widgetHeight) / 2,
            pmEnvelope->maxY + (widgetWidth - widgetHeight) / 2,
            -1.0f,
            1.0f);
    }
    //        if ( widgetHeight > widgetWidth ) {
    //            projMatrix.ortho( pmEnvelope->minX - ( widgetHeight -
    //            widgetWidth ) / 2, pmEnvelope->maxX + ( widgetHeight -
    //            widgetWidth ) / 2, pmEnvelope->minY,
    //                              pmEnvelope->maxY, -1.0f, 1.0f );
    //        } else {
    //            projMatrix.ortho( pmEnvelope->minX, pmEnvelope->maxX,
    //            pmEnvelope->minY - ( widgetWidth - widgetHeight ) / 2,
    //                              pmEnvelope->maxY + ( widgetWidth -
    //                              widgetHeight ) / 2, -1.0f, 1.0f );
    //        }
    //        projMatrix.ortho( pmEnvelope->minX, pmEnvelope->maxX,
    //        pmEnvelope->minY, pmEnvelope->maxY, -1.0f, 1.0f );
}

void GlCanvas::setRandSld() {
    PainterFactory::setRandSld();
}

void GlCanvas::getLayer(gisl::VectorLayer& layer) {
    mLayer.push_back(&layer);
    mLayerLabel.resize(layer.getFeatureCount());
    for (int i = 0; i < layer.getFeatureCount(); ++i) {
        mLayerLabel[i] = new QLabel(parentWidget());
    }
    //    for ( auto pLayer : mLayer ) {
    //        for ( int i = 0; i < pLayer->getFeatureCount(); ++i ) {
    //            auto labelPosF = projMatrix.map(
    //            pLayer->getFeature()[i]->boundary()->center()); labelPosF =
    //            scaleMatrix.map( labelPosF ); labelPosF.setX(( labelPosF.x() + 1
    //            ) * this->size().width()); labelPosF.setY(( labelPosF.y() + 1 )
    //            * this->size().height());
    ////            mLayerLabel.push_back(
    ////            auto *q =
    //            auto dd = QString(( pLayer->getFeature()[i]->getFieldAsString(
    //            pmSld->getPropertyName()).c_str()));
    ////            qDebug( "%s : %d, %d", dd.toStdString().c_str(),
    /// labelPosF.toPoint().x(), labelPosF.toPoint().y());
    //            mLayerLabel[i]->setText(
    //                    QString(( pLayer->getFeature()[i]->getFieldAsString(
    //                    pmSld->getPropertyName()).c_str()))),
    ////            q->move(labelPosF.toPoint());
    //                    mLayerLabel[i]->move( labelPosF.toPoint());
    ////            l1.setText(QString((
    /// pLayer->getFeature()[i]->getFieldAsString(
    /// pmSld->getPropertyName()).c_str()))); / l1.move(labelPosF.toPoint());
    //        }
    //    }
    //    auto *dada = new QLabel( "hrloosd", this );
    //    dada->move( 22, 45 );
}
void GlCanvas::drawRaster(std::shared_ptr<QPixmap> pixmap) {
    pmPixmap = pixmap;
}
