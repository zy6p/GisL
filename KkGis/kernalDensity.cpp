#include "kernalDensity.h"
#include "ui_kernaldensity.h"

KernalDensity::KernalDensity(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::KernalDensity) {
    ui->setupUi(this);
    this->setWindowTitle("Kernal Density");

    //���ð�ť��ͼƬ
    QIcon icoOpenFile("img/openfile.jpg");
    ui->PB_GetInputLayer->setIcon(icoOpenFile);
    ui->PB_GetInputLayer->setIconSize(QSize(28, 26));
    ui->PB_populationField->setIcon(icoOpenFile);
    ui->PB_populationField->setIconSize(QSize(28, 26));
    ui->PB_saveFilePath->setIcon(icoOpenFile);
    ui->PB_saveFilePath->setIconSize(QSize(28, 26));


    //����Area Unit��ѡ��
    ui->CB_AreaUnit->addItem("SQUARE_MAP_UNITS");//һ����������ռ�ο������Ե�λ��ƽ��������Ĭ�����á�(index=0)
    ui->CB_AreaUnit->addItem("SQUARE_KILOMETERS ");//һǧ�ס�(index=1)

    //����Output Values��ѡ��
    ui->CB_outValue->addItem("DENSITIES");//���ֵ��ʾԤ����ܶ�ֵ������Ĭ�����á�(index=0)
    ui->CB_outValue->addItem("EXPECTED_COUNTS");//���ֵ��ʾÿ����Ԫ��Ԥ�������������(index=1)

    //����Method��ѡ��
    ui->CB_Method->addItem("PLANAR");//����Ҫ��֮��ʹ��ƽ�����,����Ĭ�����á�(index=0)
    ui->CB_Method->addItem("GEODESIC");//����Ҫ��֮��ʹ�ò���߾��롣(index=1)
}

KernalDensity::~KernalDensity() {
    delete ui;
}

QString KernalDensity::getRasterSize() {
    return ui->LE_OutRasterSize->text();
}

QString KernalDensity::getSearchR() {
    return ui->LE_SearchR->text();
}

int KernalDensity::getAreaUnits() {
    return ui->CB_AreaUnit->currentIndex();
}

int KernalDensity::getOutValues() {
    return ui->CB_outValue->currentIndex();
}

int KernalDensity::getMethod() {
    return ui->CB_Method->currentIndex();
}

int KernalDensity::getInputFile() {
    return ui->CB_LayerInput->currentIndex();
}

QString KernalDensity::getOutputFile() {
    return ui->LE_OutRaster->text();
}

QString KernalDensity::getPopulation() {
    return ui->CB_Population->currentText();
}

void KernalDensity::setMap(GeoMap *mapPtr) {
    map = mapPtr;
}

void KernalDensity::getInputLayer() {
    if (map->size() != 0) {
        //����Input point or polyline��ѡ��
        QString layerName;
        int layerNum = map->size();
        for (int i = 0; i < layerNum; i++) {
            layerName = map->getLayerAt(i)->getName();
            ui->CB_LayerInput->addItem(layerName);
        }

    }
}

void KernalDensity::getPopulationField() {
    if (map->size() != 0) {
        currentLayerId = ui->CB_LayerInput->currentIndex();
        ui->CB_Population->clear();
        QList<QString> attriNames = map->getLayerAt(currentLayerId)->getAttributeNames();
        int attriNum = attriNames.size();
        for (int i = 0; i < attriNum; i++) {
            ui->CB_Population->addItem(attriNames.at(i));
        }
        ui->CB_Population->addItem("NONE");

    }
}

void KernalDensity::getRasterOut() {
    QString filePath;
    filePath = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("save file"), "",
                                            tr("JPEG(*.jpg);;PNG(*.png);;BMP(*.bmp)"));
    ui->LE_OutRaster->setText(filePath);

}


