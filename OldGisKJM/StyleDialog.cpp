#include "StyleDialog.h"
#include <qtreewidget.h>
#include <QVBoxLayout>
#include "GeoLayer.h"
#include "EnumType.h"
#include <qheaderview.h>
#include <qcolordialog.h>
#include "LineWidthDialog.h"

StyleDialog::StyleDialog(GeoLayer *layer, QWidget *parent) :
        QDialog(parent), layer(layer) {
    QVBoxLayout *layout = new QVBoxLayout();
    toolTree = new QTreeWidget();
    layout->addWidget(toolTree);
    setLayout(layout);
    resize(500, 200);
    initTree(layer);
    connect(toolTree, &QTreeWidget::itemDoubleClicked, this, &StyleDialog::on_item_clicked);
}

StyleDialog::~StyleDialog() {

}


void StyleDialog::initTree(GeoLayer *layer) {
    toolTree->header()->hide();
    int type = layer->getType();
    if (type == EnumType::POINT) {
        QIcon iconcolor, iconwidth;
        iconcolor.addFile("img/fill.png");
        iconwidth.addFile("img/line.png");

        marker = layer->getRender()->getMarkerSymbol();
        //marker_line = marker->getOutline();
        /*QTreeWidgetItem* outlineItem = new QTreeWidgetItem(QStringList() << "outline");
        toolTree->addTopLevelItem(outlineItem);*/
        QTreeWidgetItem *fillItem = new QTreeWidgetItem(QStringList() << "fill");
        toolTree->addTopLevelItem(fillItem);

        /*QTreeWidgetItem* outline_color = new QTreeWidgetItem(QStringList() << "color");
        outline_color->setIcon(0, iconcolor);
        QTreeWidgetItem* outline_width = new QTreeWidgetItem(QStringList() << "width");
        outline_width->setIcon(0, iconwidth);
        itemType.insert(outline_color, EnumType::styleType::LINECOLOR);
        itemType.insert(outline_width, EnumType::styleType::LINEWIDTH);
        outlineItem->addChild(outline_color);
        outlineItem->addChild(outline_width);*/

        QTreeWidgetItem *marker_color = new QTreeWidgetItem(QStringList() << "color");
        marker_color->setIcon(0, iconcolor);
        QTreeWidgetItem *marker_size = new QTreeWidgetItem(QStringList() << "size");
        marker_size->setIcon(0, iconcolor);
        itemType.insert(marker_color, EnumType::styleType::MARKETCOLOR);
        itemType.insert(marker_size, EnumType::styleType::MARKERSIZE);
        fillItem->addChild(marker_color);
        fillItem->addChild(marker_size);

        toolTree->expandAll();  //������֮�����
    } else if (type == EnumType::POLYLINE) {
        QIcon iconcolor, iconwidth;
        iconcolor.addFile("img/fill.png");
        iconwidth.addFile("img/line.png");

        line = layer->getRender()->getLineSymbol();
        QTreeWidgetItem *lineItem = new QTreeWidgetItem(QStringList() << "line");
        toolTree->addTopLevelItem(lineItem);

        QTreeWidgetItem *line_color = new QTreeWidgetItem(QStringList() << "color");
        line_color->setIcon(0, iconcolor);
        QTreeWidgetItem *line_width = new QTreeWidgetItem(QStringList() << "width");
        line_width->setIcon(0, iconwidth);
        itemType.insert(line_color, EnumType::LINECOLOR);
        itemType.insert(line_width, EnumType::styleType::LINEWIDTH);
        lineItem->addChild(line_color);
        lineItem->addChild(line_width);

        toolTree->expandAll();  //������֮�����
    } else if (type == EnumType::POLYGON) {

        QIcon iconcolor, iconwidth;
        iconcolor.addFile("img/fill.png");
        iconwidth.addFile("img/line.png");

        fill = layer->getRender()->getFillSymbol();
        fill_outline = fill->getOutline();
        QTreeWidgetItem *outlineItem = new QTreeWidgetItem(QStringList() << "outline");
        QTreeWidgetItem *fillItem = new QTreeWidgetItem(QStringList() << "fill");
        toolTree->addTopLevelItem(outlineItem);
        toolTree->addTopLevelItem(fillItem);

        QTreeWidgetItem *outline_color = new QTreeWidgetItem(QStringList() << "color");
        outline_color->setIcon(0, iconcolor);
        QTreeWidgetItem *outline_width = new QTreeWidgetItem(QStringList() << "width");
        outline_width->setIcon(0, iconwidth);
        itemType.insert(outline_color, EnumType::styleType::LINECOLOR);
        itemType.insert(outline_width, EnumType::styleType::LINEWIDTH);
        outlineItem->addChild(outline_color);
        outlineItem->addChild(outline_width);

        QTreeWidgetItem *fill_color = new QTreeWidgetItem(QStringList() << "color");
        fill_color->setIcon(0, iconcolor);
        itemType.insert(fill_color, EnumType::styleType::FILLCOLOR);
        fillItem->addChild(fill_color);

        toolTree->expandAll();  //������֮�����
    }
}

void StyleDialog::on_item_clicked(QTreeWidgetItem *item) {
    int featureType = layer->getType();
    if (itemType.contains(item)) {
        int type = itemType[item];   //itemType[item] ���ַ�ʽ����Ҫʹ��item��itemtype���粻��map�У����Զ����һ��Ĭ�ϵ�ֵ��value����Ҫ���ж��Ƿ����
        if (featureType == EnumType::POLYGON && type == EnumType::LINECOLOR) {
            QColor result = QColorDialog::getColor(fill_outline->getColor(), this, "fill outline color");
            if (result.isValid()) {
                fill_outline->setColor(result);
                emit renderLayerSignal(layer);
            }
        } else if (featureType == EnumType::POLYGON && type == EnumType::FILLCOLOR) {
            QColor result = QColorDialog::getColor(fill->getColor(), this, "fill color");
            if (result.isValid()) {
                fill->setColor(result);
                emit renderLayerSignal(layer);
            }
        } else if (featureType == EnumType::POLYGON && type == EnumType::LINEWIDTH) {
            LinewidthDialog dialog(fill_outline->getWidth());
            int result = dialog.exec();
            if (result == QDialog::Accepted) {
                fill_outline->setWidth(dialog.getWidth());
                emit renderLayerSignal(layer);
            }
        }
            /*else if (featureType == EnumType::POINT && type == EnumType::LINECOLOR) {
                QColor result = QColorDialog::getColor(marker_line->getColor(), this, "point outline color");
                if (result.isValid()) {
                    marker_line->setColor(result);
                    emit renderLayerSignal(layer);
                }
            }*/
        else if (featureType == EnumType::POINT && type == EnumType::MARKETCOLOR) {
            QColor result = QColorDialog::getColor(marker->getColor(), this, "point color");
            if (result.isValid()) {
                marker->setColor(result);
                emit renderLayerSignal(layer);
            }
        } else if (featureType == EnumType::POINT && type == EnumType::MARKERSIZE) {
            LinewidthDialog dialog(marker->getSize());
            int result = dialog.exec();
            if (result == QDialog::Accepted) {
                marker->setSize(dialog.getWidth());
                emit renderLayerSignal(layer);
            }
        } else if (featureType == EnumType::POLYLINE && type == EnumType::LINECOLOR) {
            QColor result = QColorDialog::getColor(line->getColor(), this, "line color");
            if (result.isValid()) {
                line->setColor(result);
                emit renderLayerSignal(layer);
            }
        } else if (featureType == EnumType::POLYLINE && type == EnumType::LINEWIDTH) {
            LinewidthDialog dialog(line->getWidth());
            int result = dialog.exec();
            if (result == QDialog::Accepted) {
                line->setWidth(dialog.getWidth());
                emit renderLayerSignal(layer);
            }
        }
    }
}
