//
// Created by km on 6/12/21.
//

#include "imgviewwidget.h"
#include "ui_imgviewwidget.h"
ImgViewWidget::ImgViewWidget(QWidget* parent) : ui(new Ui::ImgViewWidget) {
    ui->setupUi(this);
    setWindowTitle(tr("rasterImg"));
    setEnabled(true);
}
ImgViewWidget::~ImgViewWidget() {}
void ImgViewWidget::drawRaster(std::shared_ptr<QPixmap> pixmap) {
    qPixmap = pixmap;
    ui->label->setPixmap(*qPixmap);
}
void ImgViewWidget::drawPoint(gisl::ExchangePointXY& p) {}
void ImgViewWidget::drawLine(gisl::ExchangeLine& p) {}
void ImgViewWidget::drawPolygon(gisl::ExchangePolygon& p) {}
void ImgViewWidget::drawMultiPolygon(gisl::ExchangePolygon** ps, int count) {}
void ImgViewWidget::drawLinearRing(
    gisl::ExchangeLinearRing* p,
    const std::string& featureName) {}
