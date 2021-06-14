//
// Created by km on 6/13/21.
//

#include <absl/strings/str_cat.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

#include "../../ui/ui_chooserasterrgb.h"
#include "chooserasterrgbwidget.h"
#include "src/gui/render/imgviewwidget.h"

ChooseRasterRgbWidget::ChooseRasterRgbWidget(QWidget* parent)
    : ui(new Ui::ChooseRasterRgb) {
  ui->setupUi(this);
  setWindowTitle(tr("rasterImg"));
  setEnabled(true);
  QStringList qStringList;
  qStringList << "Normal"
              << "StretchToRealMinMax"
              << "StretchToCumulative96RealMinMax"
              << "StretchTo2StandardDeviation";
  this->ui->comboBoxContrast->addItems(qStringList);
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

  for (int i = 0; i < pRasterProvider->getLayerCount(); ++i) {
    auto color = qRgb(
        i * 256 / pRasterProvider->getLayerCount(),
        i * 256 / pRasterProvider->getLayerCount(),
        i * 256 / pRasterProvider->getLayerCount());
    auto* pCurve = new QwtPlotCurve{
        QString::fromStdString(absl::StrCat("band ", std::to_string(i)))};
    pCurve->setTitle(
        QString::fromStdString(absl::StrCat("band ", std::to_string(i))));
    pCurve->setPen(color, 2); //设置曲线颜色 粗细
    pCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true); //线条光滑化
    pCurve->setSamples(pRasterProvider->getPmBand()[i]
                           ->calHistogram()); //输入节点数据QPointF(x,y)
    pCurve->attach(ui->qwtPlot_1);
    pCurve->setLegendAttribute(pCurve->LegendShowLine);
    auto* symbol = new QwtSymbol(
        QwtSymbol::Ellipse,
        QBrush(color),
        QPen(QBrush{color}, 2),
        QSize(3, 3));          //设置样本点的颜色、大小
    pCurve->setSymbol(symbol); //添加样本点形状
  }
  // finally, refresh the plot
  ui->qwtPlot_1->replot();
}
void ChooseRasterRgbWidget::on_pushButton_clicked() {
  auto* iv = new ImgViewWidget(this);
  iv->show();
  this->pRasterProvider->setContrastEnhancementMethod(
      gisl::RasterBand::ContrastEnhancementMethod{
          this->ui->comboBoxContrast->currentIndex()});
  pRasterProvider->combinePrint(
      this->ui->comboBoxBand_1->currentIndex(),
      this->ui->comboBoxBand_2->currentIndex(),
      this->ui->comboBoxBand_3->currentIndex(),
      *iv);
}
