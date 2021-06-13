//
// Created by km on 6/13/21.
//

#include "chooserasterrgbwidget.h"
#include "../../ui/ui_chooserasterrgb.h"
#include "src/gui/render/imgviewwidget.h"
ChooseRasterRgbWidget::ChooseRasterRgbWidget(QWidget* parent)
    : ui(new Ui::ChooseRasterRgb) {
  ui->setupUi(this);
  setWindowTitle(tr("rasterImg"));
  setEnabled(true);
  QObject::connect(
      ui->pushButton,
      &QPushButton::clicked,
      this,
      &ChooseRasterRgbWidget::on_pushButton_clicked);
}
void ChooseRasterRgbWidget::initRgb(QStringList& q) {
  ui->comboBoxBand_1->addItems(q);
  ui->comboBoxBand_2->addItems(q);
  ui->comboBoxBand_3->addItems(q);
}
void ChooseRasterRgbWidget::setPRasterProvider(
    gisl::RasterProvider* pRasterProvider) {
  ChooseRasterRgbWidget::pRasterProvider = pRasterProvider;
  QStringList rgbBand;
  for (int i = 0; i < pRasterProvider->getLayerCount(); ++i) {
    rgbBand << QString::number(i);
  }
  this->initRgb(rgbBand);
}
void ChooseRasterRgbWidget::on_pushButton_clicked() {
  auto* iv = new ImgViewWidget(this);
  iv->show();
  pRasterProvider->combinePrint(
      this->ui->comboBoxBand_1->currentIndex(),
      this->ui->comboBoxBand_2->currentIndex(),
      this->ui->comboBoxBand_3->currentIndex(),
      *iv);
}
