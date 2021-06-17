//
// Created by km on 6/14/21.
//

#include <QFileInfo>
#include <QLineEdit>
#include <absl/strings/str_cat.h>

#include "analysisalg.h"
#include "analysisgui.h"
#include "core/layer/layertree.h"

gisl::AnalysisAlg::~AnalysisAlg() = default;
void gisl::AnalysisAlg::execute(QWidget* parent) {
    gui = new AnalysisGui{parent};
    gui->show();
    gui->setAlgName(this->_algName);
}
void gisl::AnalysisAlg::getInputComboBox(
    std::string_view sv,
    gisl::AnalysisAlg::InputArgType t) noexcept {
    switch (t) {
    case InputArgType::Layer: {
        QComboBox* comboBox = new QComboBox();
        QStringList qStringList;
        const LayerTree* layerTree = LayerTree::getLayerTree();
        for (auto [fid, pProvider] : layerTree->providerMap) {
            for (int i = 0; i < pProvider->getLayerCount(); ++i) {
                QFileInfo f{QString::fromStdString(pProvider->getFileName())};
                qStringList << QString::fromStdString(absl::StrCat(
                        std::to_string(fid),
                        ": ",
                        f.fileName().toStdString(),
                        ".",
                        std::to_string(i)));
            }
        }
        comboBox->addItems(qStringList);
        this->gui->addItemToUi(QString::fromStdString(sv.data()), comboBox);
        break;
    }
    case InputArgType::Provider: {
        QComboBox* comboBox = new QComboBox();
        QStringList qStringList;
        const LayerTree* layerTree = LayerTree::getLayerTree();
        for (auto [fid, pProvider] : layerTree->providerMap) {
            QFileInfo f{QString::fromStdString(pProvider->getFileName())};
            qStringList << QString::fromStdString(
                            absl::StrCat(std::to_string(fid), ": ", f.fileName().toStdString()));
        }
        comboBox->addItems(qStringList);
        this->gui->addItemToUi(QString::fromStdString(sv.data()), comboBox);
        break;
    }
    case InputArgType::IntValue: {
        this->gui->addItemToUi(QString::fromStdString(sv.data()), new QLineEdit{});
        break;
    }
    case InputArgType::DoubleValue: {
        this->gui->addItemToUi(QString::fromStdString(sv.data()), new QLineEdit{});
        break;
    }
    default:
        break;
    }
}
