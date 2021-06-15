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

#include <QLabel>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include "core/provider/vectorprovider.h"
#include "painter/painterfactory.h"

class GlCanvas : public QOpenGLWidget,
                 protected QOpenGLFunctions,
                 public gisl::PainterFactory {
  Q_OBJECT
public:
  explicit GlCanvas(QWidget* parent);

  ~GlCanvas() override;

  using QOpenGLWidget::QOpenGLWidget;

  //    void getEnvelope( gisl::Rectangle &rectangle ) override;

  void drawPoint(gisl::ExchangePointXY& p) override;

  void drawLine(gisl::ExchangeLine& p) override;

  void getEnvelope(gisl::Rectangle& rectangle) override;

  void getLayer(gisl::VectorLayer& layer);

  void setRandSld() override;

  void drawPolygon(gisl::ExchangePolygon& p) override;

  void drawMultiPolygon(gisl::ExchangePolygon** p, int count) override;

  void drawLinearRing(
      gisl::ExchangeLinearRing* p,
      const std::string& featureName) override;

  void drawRaster(std::shared_ptr<QPixmap> pixmap) override;

signals:

  void clicked();

protected:
  void initializeGL() override;

  void resizeGL(int w, int h) override;

  void paintGL() override;

  void mousePressEvent(QMouseEvent* event) override;

  void mouseMoveEvent(QMouseEvent* event) override;

  void mouseReleaseEvent(QMouseEvent* event) override;

  void mouseDoubleClickEvent(QMouseEvent* event) override;

  void wheelEvent(QWheelEvent* event) override;

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
  std::vector<gisl::ExchangeLinearRing*> mLinearRing;
  std::vector<std::string> mLinearRingName;
  int mLinearRingCount;

  QVector<gisl::VectorLayer*> mLayer;
  QVector<QLabel*> mLayerLabel;

  std::vector<QOpenGLVertexArrayObject*> m_vao_lineLoop;
  std::vector<QOpenGLBuffer*> m_vbo_lineLoop;
  QOpenGLShaderProgram* m_program;

  std::shared_ptr<QPixmap> pmPixmap;

  //    QOpenGLVertexArrayObject *vao;
  //    QOpenGLBuffer *vbo;
  //    QOpenGLShaderProgram *program;
  void calProjMatrix();

  void drawLabel();
};

#endif // GISL_GLCANVAS_H
