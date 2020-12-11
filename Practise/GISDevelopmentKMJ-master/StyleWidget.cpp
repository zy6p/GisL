#include "StyleWidget.h"
#include <qtreewidget.h>
#include <QVBoxLayout>
#include "GeoLayer.h"
#include "EnumType.h"
#include <qheaderview.h>
#include <qcolordialog.h>
#include "LinewidthDialog.h"

StyleWidget::StyleWidget(GeoLayer *layer, QWidget *parent) :
        QWidget(parent), layer(layer) {
    QVBoxLayout *layout = new QVBoxLayout();
    styleTree = new QTreeWidget();
    layout->addWidget(styleTree);
    setLayout(layout);
    resize(500, 200);
    initTree(layer);
    connect(styleTree, &QTreeWidget::itemDoubleClicked, this, &StyleWidget::on_item_clicked);
}

StyleWidget::~StyleWidget() {

}

void StyleWidget::closeEvent(QCloseEvent *event) {
    emit closeSignal();
}

void StyleWidget::initTree(GeoLayer *layer) {
    styleTree->header()->hide();
    int type = layer->getType();
    if (type == EnumType::POINT) {

    } else if (type == EnumType::POLYLINE) {

    } else if (type == EnumType::POLYGON) {

        QIcon iconcolor, iconwidth;
        iconcolor.addFile("img/fill.png");
        iconwidth.addFile("img/line.png");

        fill = layer->getRender()->getFillSymbol();
        outline = fill->getOutline();
        QTreeWidgetItem *outline = new QTreeWidgetItem(QStringList() << "outline");
        QTreeWidgetItem *fill = new QTreeWidgetItem(QStringList() << "fill");
        styleTree->addTopLevelItem(outline);
        styleTree->addTopLevelItem(fill);

        QTreeWidgetItem *outline_color = new QTreeWidgetItem(QStringList() << "color");
        outline_color->setIcon(0, iconcolor);
        QTreeWidgetItem *outline_width = new QTreeWidgetItem(QStringList() << "width");
        outline_width->setIcon(0, iconwidth);
        itemType.insert(outline_color, EnumType::LINECOLOR);
        itemType.insert(outline_width, EnumType::LINEWIDTH);
        outline->addChild(outline_color);
        outline->addChild(outline_width);

        QTreeWidgetItem *fill_color = new QTreeWidgetItem(QStringList() << "color");
        fill_color->setIcon(0, iconcolor);
        itemType.insert(fill_color, EnumType::FILLCOLOR);
        fill->addChild(fill_color);

        styleTree->expandAll();  //������֮�����
    }
}

void StyleWidget::on_item_clicked(QTreeWidgetItem *item) {
    if (itemType.contains(item)) {
        int type = itemType[item];   //itemType[item] ���ַ�ʽ����Ҫʹ��item��itemtype���粻��map�У����Զ����һ��Ĭ�ϵ�ֵ��value����Ҫ���ж��Ƿ����
        if (type == EnumType::LINECOLOR) {
            QColor result = QColorDialog::getColor(outline->getColor(), this, "line color");
            if (result.isValid()) {
                outline->setColor(result);
                emit renderLayerSignal(layer);
            }
        } else if (type == EnumType::FILLCOLOR) {
            QColor result = QColorDialog::getColor(fill->getColor(), this, "fill color");
            if (result.isValid()) {
                fill->setColor(result);
                emit renderLayerSignal(layer);
            }
        } else if (type == EnumType::LINEWIDTH) {
            LinewidthDialog dialog(outline->getWidth());
            int result = dialog.exec();
            if (result == QDialog::Accepted) {
                outline->setWidth(dialog.getWidth());
                emit renderLayerSignal(layer);
            } else if (result == QDialog::Rejected) {

            }
        }
    }
}
