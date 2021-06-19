//
// Created by omega on 6/18/21.
//

#include <QColor>
#include <absl/strings/str_cat.h>
#include <filesystem>

#include "analysisgui.h"
#include "core/layer/layertree.h"
#include "rsindex.h"

void gisl::RsIndex::execAlg() {
    gisl::LayerTree* layerTree = gisl::LayerTree::getLayerTree();
    auto p = layerTree->getLayerClassifyMap();

    this->realAlg(
        RsIndexMethod(this->pMethodBox->currentIndex() + 1),
        *std::get<RasterBand*>(p[std::stoi(
                                     this->pLayerBox1->currentText().toStdString().substr(0, 3))]),
        *std::get<RasterBand*>(p[std::stoi(
                                     this->pLayerBox2->currentText().toStdString().substr(0, 3))]));
}
void gisl::RsIndex::reverse() {}
const std::string& gisl::RsIndex::output() {
    return this->_errorMessage;
}
void gisl::RsIndex::execute(QWidget* parent) {
    this->_algName = tr("RsIndex").toStdString();
    AnalysisAlg::execute(parent);
}
void gisl::RsIndex::initGui() {
    AnalysisAlg::initGui();
    qDebug("initGui: %s", this->_algName.c_str());
    const auto* layerTree = LayerTree::getLayerTree();
    QStringList layerNameList;
    for (auto [fid, pLayer] : layerTree->getLayerClassifyMap()) {
        RasterBand* rsBand = std::get<RasterBand*>(pLayer);
        std::string s = std::filesystem::path(rsBand->getFileName()).filename();
        layerNameList << QString::fromStdString(absl::StrCat(
                std::to_string(rsBand->getFid()),
                ": ",
                s.substr(0, s.size() - 4)));
    }
    this->pLayerBox1 = new QComboBox{};
    this->pLayerBox2 = new QComboBox{};
    this->pLayerBox1->addItems(layerNameList);
    this->pLayerBox2->addItems(layerNameList);
    this->gui->addItemToUi(tr("first band"), this->pLayerBox1);
    this->gui->addItemToUi(tr("second band"), this->pLayerBox2);

    this->pMethodBox = new QComboBox{};
    QStringList method;
    method << "NDWI"
           << "MNDWI";
    this->pMethodBox->addItems(method);
    this->gui->addItemToUi(tr("Method"), this->pMethodBox);
}
void gisl::RsIndex::realAlg(
    RsIndexMethod m,
    RasterBand& band1,
    RasterBand& band2) {
    switch (m) {
    case gisl::RsIndex::RsIndexMethod::Normal:
        return;
    case gisl::RsIndex::RsIndexMethod::NDWI: {
        this->imgFileName = absl::StrCat(
                                band1.getFileName().substr(0, band1.getFileName().size() - 6),
                                ".NDWI",
                                ".png");
        auto greenBandData = band1.getFData();
        auto mriBandData = band2.getFData();
        this->index = (greenBandData.array() - mriBandData.array()) /
                      (greenBandData.array() + mriBandData.array());
        this->toImg();
        break;
    }
    case gisl::RsIndex::RsIndexMethod::MNDWI: {
        this->imgFileName = absl::StrCat(
                                band1.getFileName().substr(0, band1.getFileName().size() - 6),
                                ".MNDWI",
                                ".png");
        auto greenBandData = band1.getFData();
        auto mriBandData = band2.getFData();
        this->index = (greenBandData.array() - mriBandData.array()) /
                      (greenBandData.array() + mriBandData.array());
        this->toImg();
        break;
    }
    default:
        break;
    }
}
void gisl::RsIndex::toImg() {
    this->qImage =
        QImage(this->index.cols(), this->index.rows(), QImage::Format_RGB32);

    for (int i = 0; i < this->index.cols(); ++i) {
        for (int j = 0; j < this->index.rows(); ++j) {
            auto v = int((this->index(j, i) + 1) * 128);
            this->qImage.setPixel(
                i,
                j,
                qRgb(v, v, v));
        }
    }
    this->qImage.save(QString::fromStdString(this->imgFileName));
}
