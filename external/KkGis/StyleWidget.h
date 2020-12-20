#ifndef WIDGET_H
#define WIDGET_H
#include <qtreewidget.h>

#include <QWidget>
#include "GeoMap.h"

namespace Ui {
class StyleWidget;
}

class StyleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StyleWidget(GeoLayer* layer, QWidget *parent = nullptr);
    ~StyleWidget(); 

protected:
		void closeEvent(QCloseEvent *event);

private:
    Ui::StyleWidget *ui;
	QTreeWidget* styleTree;
	void initTree(GeoLayer* layer);
	GeoLayer* layer;
	LineSymbol* outline;
	FillSymbol* fill;
	QMap<QTreeWidgetItem*, int> itemType;
signals:
	void closeSignal();
	void renderLayerSignal(GeoLayer* layer);
public slots:
	void on_item_clicked(QTreeWidgetItem* item);


};

#endif // WIDGET_H
