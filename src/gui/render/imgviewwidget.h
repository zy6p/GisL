//
// Created by km on 6/12/21.
//

#ifndef GISL_IMGVIEWWIDGET_H
#define GISL_IMGVIEWWIDGET_H

#include "gui/painter/painterfactory.h"
#include <QWidget>

namespace Ui {
class ImgViewWidget;
}
class ImgViewWidget : public QWidget, public gisl::PainterFactory {
  Q_OBJECT

public:
  explicit ImgViewWidget(QWidget* parent = nullptr);

  void drawRaster(std::shared_ptr<QPixmap> pixmap) override;
  void drawPoint(gisl::ExchangePointXY& p) override;
  void drawLine(gisl::ExchangeLine& p) override;
  void drawPolygon(gisl::ExchangePolygon& p) override;
  void drawMultiPolygon(gisl::ExchangePolygon** ps, int count) override;
  void drawLinearRing(
      gisl::ExchangeLinearRing* p,
      const std::string& featureName) override;
  ~ImgViewWidget() override;

protected:
  std::shared_ptr<QPixmap> qPixmap;
  Ui::ImgViewWidget* ui;
};

#endif // GISL_IMGVIEWWIDGET_H
