#include "GlobalSearchWidget.h"
#include "ui_GlobalSearchWidget.h"
#include <NLPIR.h>
#include "qmenu.h"
#include "QListWidgetItem"

GlobalSearchWidget::GlobalSearchWidget(GeoMap* map, QWidget *parent)
	: QWidget(parent), map(map)
{
	ui = new Ui::GlobalSearchWidget();
	ui->setupUi(this);
	connect(ui->searchButton, &QPushButton::clicked, this, &GlobalSearchWidget::on_searchButton_clicked); 
	if (!NLPIR_Init(0,1)) {
		qWarning() << QStringLiteral("NLPIR初始化失败");
	}
	initRightedMenu();
	connect(ui->resultList, &QListWidget::itemDoubleClicked, this, &GlobalSearchWidget::on_item_doubleClicked);
}

GlobalSearchWidget::~GlobalSearchWidget()
{
	if (NLPIR_Exit()) {
		qWarning() << QStringLiteral("分词系统退出失败");
	}
	delete ui;
}

void GlobalSearchWidget::on_searchButton_clicked()
{
	QString quary = ui->searchInputTextEdit->text();
	if (quary != "") {
		ui->resultList->clear();
		const char* result = NLPIR_ParagraphProcess(quary.toStdString().c_str());
		QString pardsStr = QString::fromLocal8Bit(result);
		QStringList partList = pardsStr.split(" ");
		int row = 0;
		for (int i = 0; i < partList.size() - 1; i++) {
			QString part = partList.at(i);
			QString word = part.mid(0, part.indexOf("/"));
			QString partOfSpeech = part.mid(part.indexOf("/") + 1);
			for (int j = 0; j < map->size(); j++) {
				GeoLayer* layer = map->getLayerAt(j);
				QString attriName = layer->getGlobalDefaultColomn();
				QList<GeoFeature*> features = layer->search(attriName, word);
				for (int z = 0; z < features.size(); z++) {
					GeoFeature* feature = features.at(z);
					QMap<QString, QVariant>* map = feature->getAttributeMap();
					ui->resultList->addItem((*map)[attriName].toString());
					rowFeatureMap.insert(row++, feature);
				}
			}
		}
	}
}


void GlobalSearchWidget::on_zoomToFeature_action_triggered()
{
	int row = ui->resultList->currentIndex().row();
	emit zoomToFeatureSignal(rowFeatureMap[row]);
}

void GlobalSearchWidget::on_transToFeature_action_triggered()
{
	int row = ui->resultList->currentIndex().row();
	emit transToFeatureSignal(rowFeatureMap[row]);
}

void GlobalSearchWidget::on_fileTree_contextMenu_request(const QPoint & pos)
{
	//处理filetree右键事件
	if (ui->resultList->currentItem() == NULL) {
		return;
	}
	itemMenu->exec(QCursor::pos());
}

void GlobalSearchWidget::on_item_doubleClicked(QListWidgetItem * item)
{
	int row = ui->resultList->row(item);
	emit selectFeatureSignal(rowFeatureMap[row]);
}



void GlobalSearchWidget::initRightedMenu()
{
	itemMenu = new QMenu(this);
	QAction* zoomToFeatureAction = itemMenu->addAction(QString("zoom to feature"));
	QAction* translateToFeatureAction = itemMenu->addAction(QString("translate to feature"));
	connect(zoomToFeatureAction, &QAction::triggered, this, &GlobalSearchWidget::on_zoomToFeature_action_triggered);
	connect(translateToFeatureAction, &QAction::triggered, this, &GlobalSearchWidget::on_transToFeature_action_triggered);

	ui->resultList->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->resultList, &QListWidget::customContextMenuRequested, this, &GlobalSearchWidget::on_fileTree_contextMenu_request);
}