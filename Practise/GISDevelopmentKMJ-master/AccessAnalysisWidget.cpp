#include "AccessAnalysisWidget.h"
#include "ui_AccessAnalysisWidget.h"
#include "GeoMap.h"
#include "AccessibilityOption.h"
#include "AccessibilityAnalysisTool.h"

AccessAnalysisWidget::AccessAnalysisWidget(GeoMap *map, QWidget *parent)
        : QWidget(parent), map(map), oriBoxSelectHint(QStringLiteral("����ǰͼ����ѡ��Ҫ����Ϊ��ѯ���")) {
    ui = new Ui::AccessAnalysisWidget();
    ui->setupUi(this);
    initWidget();
    connect(ui->okButton, &QPushButton::clicked, this, &AccessAnalysisWidget::on_runTool);
    connect(ui->cancelButton, &QPushButton::clicked, this, &AccessAnalysisWidget::close);
}

AccessAnalysisWidget::~AccessAnalysisWidget() {
    delete ui;
}

void AccessAnalysisWidget::initWidget() {
    ui->oriBox->clear();
    ui->oriBox->addItem(oriBoxSelectHint);
    ui->dirPointLayerBox->clear();
    ui->arcBox->clear();
    ui->nodeBox->clear();
    ui->timeLimitTextLine->setText("");
    ui->saveFieldTextLine->setText("");
    for (int i = 0; i < map->size(); i++) {
        GeoLayer *layer = map->getLayerAt(i);
        int type = layer->getType();
        if (type == EnumType::POINT) {
            ui->oriBox->addItem(layer->getName(), QVariant(layer->getFullPath()));
            ui->dirPointLayerBox->addItem(layer->getName(), QVariant(layer->getFullPath()));
            ui->nodeBox->addItem(layer->getName(), QVariant(layer->getFullPath()));
        } else if (type == EnumType::POLYLINE) {
            ui->arcBox->addItem(layer->getName(), QVariant(layer->getFullPath()));
        }
    }
}

void AccessAnalysisWidget::connectDatabase(QString databaseUrl) {
    PostgisHelper helper(databaseUrl);
    if (!dataset) {
        dataset->Release();
        delete dataset;
    }
    dataset = helper.getDataSet();
}

bool AccessAnalysisWidget::isValid() {
    bool validity = true;
    QString test = ui->oriBox->currentData().toString();
    GeoLayer *oriLayer = map->getLayerByFullpath(ui->oriBox->currentData().toString());
    float timeLimit = ui->timeLimitTextLine->text().toFloat();
    QString saveField = ui->saveFieldLabel->text();
    if (timeLimit <= 0) validity = false;  //timeLimit�������0
    if (oriLayer->getAttributeNames().contains(saveField)) validity = false;  //�ֶβ�������
    return validity;
}

void AccessAnalysisWidget::on_runTool() {
    if (isValid()) {
        AccessibilityOption *option = new AccessibilityOption;
        if (ui->oriBox->currentData().toString() == oriBoxSelectHint) {  //����ǽ���ǰͼ��ѡȡ��Ҫ����Ϊ������
            option->setOriLayer(map->getCurrentLayer());
            option->setUseSelectedFeatures(true);
        } else {
            option->setOriLayer(map->getLayerByFullpath(ui->oriBox->currentData().toString()));
            option->setUseSelectedFeatures(false);
        }
        option->setDirPointLayer(map->getLayerByFullpath(ui->dirPointLayerBox->currentData().toString()));
        option->setNodeLayer(map->getLayerByFullpath(ui->nodeBox->currentData().toString()));
        option->setArcLayer(map->getLayerByFullpath(ui->arcBox->currentData().toString()));
        option->setSaveField(ui->saveFieldTextLine->text());
        option->setTimeLimit(ui->timeLimitTextLine->text().toFloat());
        AccessibilityAnalysisTool *tool = new AccessibilityAnalysisTool;
        tool->setOption(option);
        tool->run_tool();
    }
}
