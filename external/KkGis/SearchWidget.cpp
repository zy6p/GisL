#include "SearchWidget.h"
#include "ui_SearchWidget.h"
#include "qdebug.h"
#include <qtextcodec.h>
#include <qmenu.h>
#include <qaction.h>

SearchWidget::SearchWidget(GeoLayer* layer, QWidget *parent)
	: QWidget(parent),layer(layer),ui(new Ui::SearchWidget)
{
	ui->setupUi(this);
	QList<QString> layerNames = layer->getAttributeNames();
	for (int i = 0; i < layerNames.size(); i++) {
		ui->attriNameComboBox->addItem(layerNames.at(i));
	}
	connect(ui->searchButton, &QPushButton::clicked, this, &SearchWidget::on_search_button_clicked);
	initRightedMenu();
	connect(ui->searchResultList, &QListWidget::itemDoubleClicked, this, &SearchWidget::on_item_doubleClicked);
}

SearchWidget::~SearchWidget()
{
}

void SearchWidget::initRightedMenu()
{
	itemMenu = new QMenu(this);
	QAction* zoomToFeatureAction = itemMenu->addAction(QString("zoom to feature"));
	QAction* translateToFeatureAction = itemMenu->addAction(QString("translate to feature"));
	connect(zoomToFeatureAction, &QAction::triggered, this, &SearchWidget::on_zoomToFeature_action_triggered);
	connect(translateToFeatureAction, &QAction::triggered, this, &SearchWidget::on_transToFeature_action_triggered);

	ui->searchResultList->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->searchResultList, &QListWidget::customContextMenuRequested, this, &SearchWidget::on_fileTree_contextMenu_request);
}

void SearchWidget::closeEvent(QCloseEvent * event)
{
	emit closeSignal();
}

void SearchWidget::on_search_button_clicked()
{
	QString attriName = ui->attriNameComboBox->currentText();
	QString attriValue = ui->attributeValueInputLine->text();
	if (attriValue != "") {
		if (ui->searchResultList->count()) {
			ui->searchResultList->clear();
			rowFeatureMap.clear();
		}
		QList<GeoFeature*> features = layer->search(attriName, attriValue);
		for (int i = 0; i < features.size(); i++) {
			GeoFeature* feature = features.at(i);
			QMap<QString, QVariant>* map = feature->getAttributeMap();
			ui->searchResultList->addItem((*map)[attriName].toString());
			rowFeatureMap.insert(i, feature);
		}
		//这里的数字不能使用0，因为qstring会认为使用的是qstring(qchar)而不是qstirng(int)，这里应该使用QString(int size, QChar ch)或者QString::number(int）
		//经过测试可以使用QStringLiteral和textcdoc正确处理中文，而qstring：：fromlatin8无效
		ui->resultNumLabel->setText(QStringLiteral("共查询出") + QString::number(features.size()) + QStringLiteral("条结果"));
	}
	else {
		qDebug() << "not attribute value";
	}
}


void SearchWidget::on_zoomToFeature_action_triggered()
{
	int row = ui->searchResultList->currentIndex().row();
	emit zoomToFeatureSignal(rowFeatureMap[row]);
}

void SearchWidget::on_transToFeature_action_triggered()
{
	int row = ui->searchResultList->currentIndex().row();
	emit transToFeatureSignal(rowFeatureMap[row]);
}

void SearchWidget::on_fileTree_contextMenu_request(const QPoint & pos)
{
	//处理filetree右键事件
	if (ui->searchResultList->currentItem() == NULL) {
		return;
	}
	itemMenu->exec(QCursor::pos());
}

void SearchWidget::on_item_doubleClicked(QListWidgetItem * item)
{
	int row = ui->searchResultList->row(item);
	emit selectFeatureSignal(rowFeatureMap[row]);
}

