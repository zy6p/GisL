#include "MyTreeWidget.h"


MyTreeWidget::MyTreeWidget(QWidget *parent)
	:QTreeWidget(parent)
{
	ui.setupUi(this);
	//ui.treeWidget->setHeaderHidden(true);
	this->setHeaderLabel(QString::fromLocal8Bit("图层"));
	dialog = new Dialog();
	attri = new AttributeTable();
	layerColoursSet = new LayerColoursSet();
	createActions();
	createMenu();
	setContextMenuPolicy(Qt::CustomContextMenu);  //设置枚举值
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(sltShowPopMenu(const QPoint&)));
	connect(dialog, SIGNAL(sendColorAndWidthData(QColor ,QColor,float )),this, SLOT(getColorAndWidth(QColor,QColor ,float )));
	loc = 0;
	deletesize = 0;
}


MyTreeWidget::~MyTreeWidget(void)
{
}

void MyTreeWidget::updateMyTreeWidgetSlot(CGeoMap *map){
	this->clear();
	this->map = map;
	for(int i=0;i<map->geoLayers.size();i++){
		QTreeWidgetItem *item = new QTreeWidgetItem(this,QStringList(map->geoLayers[i]->getLayerName()));
		if(map->geoLayers[i]->getVisible())
			item->setCheckState(0,Qt::Checked);
		else
			item->setCheckState(0,Qt::Unchecked);
	}
}

void MyTreeWidget::itemClick(){
	QTreeWidgetItemIterator it(this);
	int count = 0;
	while (*it) {
		if((*it)->checkState(0)==Qt::Checked){
			map->geoLayers[count]->setVisible(true);
		}
		else{
			map->geoLayers[count]->setVisible(false);
		}
		++it;
		count++;
	}
	int mode = 3;
	emit updateTreeGLSignal(mode,this->map,loc,0);
}

void MyTreeWidget::createActions(){
	//connect(ui.view_this, &QAction::triggered, this, &MyTreeWidget::viewIt);
	connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(itemClick()),Qt::UniqueConnection);
	connect(this,SIGNAL(showAttri(CGeoLayer*)),attri,SLOT(showAttri(CGeoLayer*)),Qt::UniqueConnection);
	connect(this,SIGNAL(setLayerClours(int ,QString ,QList<QString> )),layerColoursSet,SLOT(setAttribute(int ,QString ,QList<QString>)),Qt::UniqueConnection);
	connect(layerColoursSet,SIGNAL(setLayerClours(int ,QString  )),this,SLOT(getAttribute(int ,QString )),Qt::UniqueConnection);

}

void MyTreeWidget::createMenu(){
	popMenu = new QMenu(this);
	QAction* act = popMenu->addAction("viewIt");
	connect(act, SIGNAL(triggered(bool)), this, SLOT(viewIt()));
	QAction* act2 = popMenu->addAction("deleteIt");
	connect(act2, SIGNAL(triggered(bool)), this, SLOT(deleteIt()));
	QAction* act3 = popMenu->addAction("properties");
	connect(act3, SIGNAL(triggered(bool)), this, SLOT(serProp()));
	QAction* act4 = popMenu->addAction("Open Attribute table");
	connect(act4, SIGNAL(triggered(bool)), this, SLOT(openAttri()));
	QAction* act5 = popMenu->addAction("showIndexGrids");
	connect(act5, SIGNAL(triggered(bool)), this, SLOT(showIndexGrids()));
	QAction* act6 = popMenu->addAction("hideIndexGrids");
	connect(act6, SIGNAL(triggered(bool)), this, SLOT(hideIndexGrids()));
	QAction* act7 = popMenu->addAction("KDE");
	connect(act7, SIGNAL(triggered(bool)), this, SLOT(analyzeKDE()));
	QAction* act8 = popMenu->addAction("Layer Colours");
	connect(act8, SIGNAL(triggered(bool)), this, SLOT(layerColours()));
}

void MyTreeWidget::layerColours(){
	QModelIndex index = this->currentIndex();
	int layerID = index.row();
	QString layerNAME = map->geoLayers[layerID]->getLayerName();
	QList<QString> propsKey = map->geoLayers[layerID]->getPropsKey();
	emit setLayerClours(layerID,layerNAME,propsKey);
	layerColoursSet->show();
}
void MyTreeWidget::sltShowPopMenu(const QPoint& pos)//槽函数
{

	curItem = this->itemAt(pos);

	if (curItem == NULL)return;
	//curItem = ui.treeWidget->currentItem();  //获取当前被点击的节点
	//如果没有点击到节点
	popMenu->exec(QCursor::pos());
}

void MyTreeWidget::serProp(){

	dialog->show();
}

void MyTreeWidget::openAttri(){
	QModelIndex index = this->currentIndex();
	int layerID = index.row();
	CGeoLayer *layer = map->geoLayers[layerID];
	// 属性表展示
	emit showAttri(layer);
}

void MyTreeWidget::showIndexGrids(){
	QModelIndex index = this->currentIndex();
	int layerID = index.row();
	CGeoLayer *layer = map->geoLayers[layerID];
	layer->showIndexGrid = true;
	emit IndexGrids();
}

void MyTreeWidget::hideIndexGrids(){
	QModelIndex index = this->currentIndex();
	int layerID = index.row();
	CGeoLayer *layer = map->geoLayers[layerID];
	layer->showIndexGrid = false;
	emit IndexGrids();
}

void MyTreeWidget::getColorAndWidth(QColor fillColor,QColor strokeColor,float width){
	QModelIndex index = this->currentIndex();
	int layerID = index.row();
	emit sendColorAndWidthData(layerID,fillColor,strokeColor,width);
}

void MyTreeWidget::getAttribute(int layerID,QString attribute){
	emit setLayerCol(layerID,attribute);
}

//右键选项的执行函数
void MyTreeWidget::viewIt()
{
	QModelIndex index = this->currentIndex();
	int layerID = index.row();
	int mode = 5;
	emit updateLayerIDSignal(mode,layerID);

}

//右键选项的执行函数
void MyTreeWidget::deleteIt()
{
	// 删除map的第几个
	QModelIndex index = this->currentIndex();
	int layerID = index.row();
	int objectsize = 1;
	if(map->geoLayers[layerID]->type!=0)
		objectsize = map->geoLayers[layerID]->geoObjects.size();
	map->deleteLayerAt(layerID);
	// 通知myclass
	int mode = 4;
	this->loc = layerID;
	this->deletesize = objectsize;
	emit updateTreeGLSignal(mode,this->map,layerID,objectsize);
	// 刷新菜单
	updateMyTreeWidgetSlot(this->map);
}

void MyTreeWidget::analyzeKDE(){
	// 删除map的第几个
	QModelIndex index = this->currentIndex();
	int layerID = index.row();
	if(map->geoLayers[layerID]->type!=0){
		QMessageBox::critical(NULL, QString::fromLocal8Bit("不支持的类型"), QString::fromLocal8Bit("仅支持对点要素图层进行核密度分析"), QMessageBox::Yes, QMessageBox::Yes);  
		return;
	}
	emit KDEAnalyze(layerID);
}