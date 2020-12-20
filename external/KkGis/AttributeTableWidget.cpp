#include "AttributeTableWidget.h"
#include "ui_AttributeTableWidget.h"
#include <QVBoxLayout>
#include <qheaderview.h>
#include <qmenu.h>

AttributeTableWidget::AttributeTableWidget(GeoLayer* layer, QWidget *parent)
	: QWidget(parent),layer(layer), originFeatures(layer->getAllFeature()), startRow(-1),endRow(-1),keyPressed(Qt::Key_No)
{
	ui = new Ui::AttributeTableWidget();
	ui->setupUi(this);
	setFocusPolicy(Qt::StrongFocus);

	QVBoxLayout* mainLayout = new QVBoxLayout();
	setLayout(mainLayout);
	table = new QTableWidget();
	mainLayout->addWidget(table);
    initTable();
	initRightedMenu();
}

AttributeTableWidget::~AttributeTableWidget()
{
	delete ui;
}

void AttributeTableWidget::closeEvent(QCloseEvent * event)
{
	emit closeSignal(event);
}

void AttributeTableWidget::keyPressEvent(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key_Shift:
		keyPressed = Qt::Key_Shift;
		layer->setSelectMode(EnumType::selectMode::MULTIMODE);
		break;
	case Qt::Key_Control:
		keyPressed = Qt::Key_Control;
		layer->setSelectMode(EnumType::selectMode::MULTIMODE);
		break;
	default:
		break;
	}
}

void AttributeTableWidget::keyReleaseEvent(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key_Shift:
		keyPressed = Qt::Key_No;
		layer->setSelectMode(EnumType::selectMode::SINGLEMODE);
		break; 
	case Qt::Key_Control:
		keyPressed = Qt::Key_No;
		layer->setSelectMode(EnumType::selectMode::SINGLEMODE);
		break;
	default:
		break;
	}
}

void AttributeTableWidget::initTable()
{
	QList<QString> attriNames = layer->getAttributeNames();
	int rowNum = layer->size();
	int colNum = attriNames.size();
	table->setColumnCount(colNum);  //设置行数
	QStringList colomnNameList;
	for (int i = 0; i < colNum; i++) {  //设置行宽
		table->setColumnWidth(i, 100);
		colomnNameList.append(attriNames.at(i));
	}
	table->setHorizontalHeaderLabels(colomnNameList);
	//table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); //行宽可自定义
	table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);  
	table->horizontalHeader()->setHighlightSections(false);
	table->setRowCount(rowNum);

	//填充数据
	for (int i = 0; i < rowNum; i++) {
		GeoFeature* feature = originFeatures.at(i);
		featureRowMap.insert(feature, i);
		QMap<QString, QVariant>* map = feature->getAttributeMap();
		for (int j = 0; j < colNum; j++) {
			QString attriName = attriNames.at(j);
			table->setItem(i, j, new QTableWidgetItem((*map)[attriName].toString()));
		}
	}
	connect(table, &QTableWidget::itemClicked, this, &AttributeTableWidget::on_item_clicked);
}

void AttributeTableWidget::initRightedMenu()
{
	itemMenu = new QMenu(this);
	QAction* zoomToFeatureAction = itemMenu->addAction(QString("zoom to feature"));
	QAction* translateToFeatureAction = itemMenu->addAction(QString("translate to feature"));
	connect(zoomToFeatureAction, &QAction::triggered, this, &AttributeTableWidget::on_zoomToFeature_action_triggered);
	connect(translateToFeatureAction, &QAction::triggered, this, &AttributeTableWidget::on_transToFeature_action_triggered);

	table->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(table, &QTableWidget::customContextMenuRequested, this, &AttributeTableWidget::on_fileTree_contextMenu_request);
}

void AttributeTableWidget::on_zoomToFeature_action_triggered()
{
	int row = table->currentRow();
	emit zoomToFeatureSignal(originFeatures.at(row));
}

void AttributeTableWidget::on_transToFeature_action_triggered()
{
	int row = table->currentRow();
	emit transToFeatureSignal(originFeatures.at(row));
}

void AttributeTableWidget::on_fileTree_contextMenu_request(const QPoint & pos)
{
	//处理filetree右键事件
	if (table->currentItem() == NULL) {
		return;
	}
	itemMenu->exec(QCursor::pos());
}

void AttributeTableWidget::on_glFeatureSelected(GeoFeature * feature)
{
	if (!feature) {  //为空就清空选择
		table->clearSelection();
		return;
	}
	if (keyPressed == Qt::Key_No) {  //此时为单选模式
		startRow = featureRowMap[feature];
		table->clearSelection();
		table->selectRow(startRow);
	}
	/*else if (keyPressed == Qt::Key_Shift) {  //此时为连选模式
		if (startRow == -1) {
			startRow = featureRowMap[feature];
			table->clearSelection();
			table->selectRow(startRow);
		}
		else {
			endRow = featureRowMap[feature];
			table->clearSelection();
			if (startRow > endRow) {
				for (int i = startRow; i >= endRow; i--) {
					table->selectRow(i);
				}
			}
			else {
				for (int i = startRow; i < endRow; i++) {
					table->selectRow(i);
				}
			}
		}
	}*/  //对于图层的选择不需要连选模式
	else if (keyPressed == Qt::Key_Control) {  //此为多选模式
		startRow = featureRowMap[feature];
		table->selectRow(startRow);
	}
}

void AttributeTableWidget::on_item_clicked(QTableWidgetItem* item)
{
	if (keyPressed == Qt::Key_No) {   //没有按住按键时，为单选模式
		startRow = table->row(item);
		GeoFeature* feature = originFeatures.at(startRow);
		layer->selectFeature(feature);
	}
	else if (keyPressed == Qt::Key_Shift) {  //按住shift时，为多选模式
		if (startRow == -1) {
			startRow = table->row(item);
			GeoFeature* feature = originFeatures.at(startRow);
			layer->selectFeature(feature);
		}
		else {
			endRow = table->row(item);
			layer->clearSelections();
			if (startRow > endRow) {
				for (int i = startRow; i >= endRow; i--) {
					GeoFeature* feature = originFeatures.at(i);
					layer->selectFeature(feature);
				}
			}
			else {
				for (int i = startRow; i < endRow; i++) {
					GeoFeature* feature = originFeatures.at(i);
					layer->selectFeature(feature);
				}
			}
		}
	}
	else if (keyPressed == Qt::Key_Control) {  //按住control时，为跳选模式
		startRow = table->row(item);
		GeoFeature* feature = originFeatures.at(startRow);
		layer->selectFeature(feature);
	}
	emit updateMapSignal();
}
