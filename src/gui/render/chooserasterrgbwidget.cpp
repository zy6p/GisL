//
// Created by km on 6/13/21.
//

#include <QColor>
#include <absl/strings/str_cat.h>
#include <queue>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

#include "chooserasterrgbwidget.h"
#include "gui/render/imgviewwidget.h"
#include "ui_chooserasterrgb.h"

ChooseRasterRgbWidget::ChooseRasterRgbWidget(QWidget* parent)
    : ui(new Ui::ChooseRasterRgb) {
    ui->setupUi(this);
    setWindowTitle(tr("Image"));
    setEnabled(true);
    QStringList qStringList;
    qStringList << QLatin1String("Normal") << QLatin1String("StretchToRealMinMax")
                << QLatin1String("StretchToCumulative96RealMinMax")
                << QLatin1String("StretchTo2StandardDeviation");
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

    std::queue<QColor> colorQueue;
    colorQueue.push(QColor(Qt::red));
    colorQueue.push(QColor(Qt::green));
    colorQueue.push(QColor(Qt::blue));
    colorQueue.push(QColor(Qt::black));
    colorQueue.push(QColor(Qt::darkRed));
    colorQueue.push(QColor(Qt::darkGreen));
    colorQueue.push(QColor(Qt::darkBlue));
    colorQueue.push(QColor(Qt::cyan));
    colorQueue.push(QColor(Qt::darkCyan));
    colorQueue.push(QColor(Qt::magenta));
    colorQueue.push(QColor(Qt::darkMagenta));
    colorQueue.push(QColor(Qt::yellow));
    colorQueue.push(QColor(Qt::darkYellow));
    colorQueue.push(QColor(Qt::gray));
    colorQueue.push(QColor(Qt::darkGray));
    colorQueue.push(QColor(Qt::lightGray));
    colorQueue.push(QColor(68, 1, 8));
    colorQueue.push(QColor(70, 49, 12));
    colorQueue.push(QColor(54, 92, 14));
    colorQueue.push(QColor(39, 127, 14));
    colorQueue.push(QColor(31, 162, 13));
    colorQueue.push(QColor(73, 194, 10));
    colorQueue.push(QColor(160, 218, 5));
    colorQueue.push(QColor(254, 231, 3));

    for (int i = 0; i < pRasterProvider->getLayerCount(); ++i) {
        auto color = colorQueue.front();
        colorQueue.pop();
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
