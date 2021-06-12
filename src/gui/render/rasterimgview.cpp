//
// Created by km on 6/12/21.
//

#include "rasterimgview.h"
#include "../../ui/ui_rasterimgview.h"
RasterImgView::RasterImgView(QWidget* parent)
    : QGraphicsView(parent), ui(new Ui::RasterImgView) {
  ui->setupUi(this);
  setWindowTitle(tr("rasterImg"));
  setEnabled(true);
}
void RasterImgView::paintEvent(QPaintEvent* event) {
  QPainter painter{this};
  painter.drawPixmap(0, 0, *qPixmap);
}
void RasterImgView::drawRaster(std::unique_ptr<QPixmap> pixmap) {
  qPixmap = std::move(pixmap);
}
void RasterImgView::drawPoint(gisl::ExchangePointXY& p) {}
void RasterImgView::drawLine(gisl::ExchangeLine& p) {}
void RasterImgView::drawPolygon(gisl::ExchangePolygon& p) {}
void RasterImgView::drawMultiPolygon(gisl::ExchangePolygon** ps, int count) {}
void RasterImgView::drawLinearRing(
    gisl::ExchangeLinearRing* p,
    const std::string& featureName) {}
