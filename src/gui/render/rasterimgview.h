//
// Created by km on 6/12/21.
//

#ifndef GISL_RASTERIMGVIEW_H
#define GISL_RASTERIMGVIEW_H

#include <QGraphicsView>
#include <src/gui/painter/painterfactory.h>

namespace Ui {
class RasterImgView;
}
class RasterImgView : public QGraphicsView, public gisl::PainterFactory {
  Q_OBJECT

public:
  explicit RasterImgView(QWidget* parent = nullptr);

  void drawRaster(std::shared_ptr<QPixmap> pixmap) override;
  void drawPoint(gisl::ExchangePointXY& p) override;
  void drawLine(gisl::ExchangeLine& p) override;
  void drawPolygon(gisl::ExchangePolygon& p) override;
  void drawMultiPolygon(gisl::ExchangePolygon** ps, int count) override;
  void drawLinearRing(
      gisl::ExchangeLinearRing* p,
      const std::string& featureName) override;

protected:
  void paintEvent(QPaintEvent* event) override;
  std::shared_ptr<QPixmap> qPixmap;
  Ui::RasterImgView* ui;
};

#endif // GISL_RASTERIMGVIEW_H
