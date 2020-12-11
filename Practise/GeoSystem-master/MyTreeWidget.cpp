#include "MyTreeWidget.h"


MyTreeWidget::MyTreeWidget(QWidget *parent)
        : QTreeWidget(parent) {
    ui.setupUi(this);
    //ui.treeWidget->setHeaderHidden(true);
    this->setHeaderLabel(QString::fromLocal8Bit("ͼ��"));
    dialog = new Dialog();
    attri = new AttributeTable();
    layerColoursSet = new LayerColoursSet();
    createActions();
    createMenu();
    setContextMenuPolicy(Qt::CustomContextMenu);  //����ö��ֵ
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(sltShowPopMenu(const QPoint&)));
    connect(dialog, SIGNAL(sendColorAndWidthData(QColor, QColor, float)), this,
            SLOT(getColorAndWidth(QColor, QColor, float)));
    loc = 0;
    deletesize = 0;
}


MyTreeWidget::~MyTreeWidget(void) {
}

void MyTreeWidget::updateMyTreeWidgetSlot(CGeoMap *map) {
    this->clear();
    this->map = map;
    for (int i = 0; i < map->geoLayers.size(); i++) {
        QTreeWidgetItem *item = new QTreeWidgetItem(this, QStringList(map->geoLayers[i]->getLayerName()));
        if (map->geoLayers[i]->getVisible())
            item->setCheckState(0, Qt::Checked);
        else
            item->setCheckState(0, Qt::Unchecked);
    }
}

void MyTreeWidget::itemClick() {
    QTreeWidgetItemIterator it(this);
    int count = 0;
    while (*it) {
        if ((*it)->checkState(0) == Qt::Checked) {
            map->geoLayers[count]->setVisible(true);
        } else {
            map->geoLayers[count]->setVisible(false);
        }
        ++it;
        count++;
    }
    int mode = 3;
    emit updateTreeGLSignal(mode, this->map, loc, 0);
}

void MyTreeWidget::createActions() {
    //connect(ui.view_this, &QAction::triggered, this, &MyTreeWidget::viewIt);
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem * , int)), this, SLOT(itemClick()), Qt::UniqueConnection);
    connect(this, SIGNAL(showAttri(CGeoLayer * )), attri, SLOT(showAttri(CGeoLayer * )), Qt::UniqueConnection);
    connect(this, SIGNAL(setLayerClours(int, QString, QList<QString>)), layerColoursSet,
            SLOT(setAttribute(int, QString, QList<QString>)), Qt::UniqueConnection);
    connect(layerColoursSet, SIGNAL(setLayerClours(int, QString)), this, SLOT(getAttribute(int, QString)),
            Qt::UniqueConnection);

}

void MyTreeWidget::createMenu() {
    popMenu = new QMenu(this);
    QAction *act = popMenu->addAction("viewIt");
    connect(act, SIGNAL(triggered(bool)), this, SLOT(viewIt()));
    QAction *act2 = popMenu->addAction("deleteIt");
    connect(act2, SIGNAL(triggered(bool)), this, SLOT(deleteIt()));
    QAction *act3 = popMenu->addAction("properties");
    connect(act3, SIGNAL(triggered(bool)), this, SLOT(serProp()));
    QAction *act4 = popMenu->addAction("Open Attribute table");
    connect(act4, SIGNAL(triggered(bool)), this, SLOT(openAttri()));
    QAction *act5 = popMenu->addAction("showIndexGrids");
    connect(act5, SIGNAL(triggered(bool)), this, SLOT(showIndexGrids()));
    QAction *act6 = popMenu->addAction("hideIndexGrids");
    connect(act6, SIGNAL(triggered(bool)), this, SLOT(hideIndexGrids()));
    QAction *act7 = popMenu->addAction("KDE");
    connect(act7, SIGNAL(triggered(bool)), this, SLOT(analyzeKDE()));
    QAction *act8 = popMenu->addAction("Layer Colours");
    connect(act8, SIGNAL(triggered(bool)), this, SLOT(layerColours()));
}

void MyTreeWidget::layerColours() {
    QModelIndex index = this->currentIndex();
    int layerID = index.row();
    QString layerNAME = map->geoLayers[layerID]->getLayerName();
    QList<QString> propsKey = map->geoLayers[layerID]->getPropsKey();
    emit setLayerClours(layerID, layerNAME, propsKey);
    layerColoursSet->show();
}

void MyTreeWidget::sltShowPopMenu(const QPoint &pos)//�ۺ���
{

    curItem = this->itemAt(pos);

    if (curItem == NULL)return;
    //curItem = ui.treeWidget->currentItem();  //��ȡ��ǰ������Ľڵ�
    //���û�е�����ڵ�
    popMenu->exec(QCursor::pos());
}

void MyTreeWidget::serProp() {

    dialog->show();
}

void MyTreeWidget::openAttri() {
    QModelIndex index = this->currentIndex();
    int layerID = index.row();
    CGeoLayer *layer = map->geoLayers[layerID];
    // ���Ա�չʾ
    emit showAttri(layer);
}

void MyTreeWidget::showIndexGrids() {
    QModelIndex index = this->currentIndex();
    int layerID = index.row();
    CGeoLayer *layer = map->geoLayers[layerID];
    layer->showIndexGrid = true;
    emit IndexGrids();
}

void MyTreeWidget::hideIndexGrids() {
    QModelIndex index = this->currentIndex();
    int layerID = index.row();
    CGeoLayer *layer = map->geoLayers[layerID];
    layer->showIndexGrid = false;
    emit IndexGrids();
}

void MyTreeWidget::getColorAndWidth(QColor fillColor, QColor strokeColor, float width) {
    QModelIndex index = this->currentIndex();
    int layerID = index.row();
    emit sendColorAndWidthData(layerID, fillColor, strokeColor, width);
}

void MyTreeWidget::getAttribute(int layerID, QString attribute) {
    emit setLayerCol(layerID, attribute);
}

//�Ҽ�ѡ���ִ�к���
void MyTreeWidget::viewIt() {
    QModelIndex index = this->currentIndex();
    int layerID = index.row();
    int mode = 5;
    emit updateLayerIDSignal(mode, layerID);

}

//�Ҽ�ѡ���ִ�к���
void MyTreeWidget::deleteIt() {
    // ɾ��map�ĵڼ���
    QModelIndex index = this->currentIndex();
    int layerID = index.row();
    int objectsize = 1;
    if (map->geoLayers[layerID]->type != 0)
        objectsize = map->geoLayers[layerID]->geoObjects.size();
    map->deleteLayerAt(layerID);
    // ֪ͨmyclass
    int mode = 4;
    this->loc = layerID;
    this->deletesize = objectsize;
    emit updateTreeGLSignal(mode, this->map, layerID, objectsize);
    // ˢ�²˵�
    updateMyTreeWidgetSlot(this->map);
}

void MyTreeWidget::analyzeKDE() {
    // ɾ��map�ĵڼ���
    QModelIndex index = this->currentIndex();
    int layerID = index.row();
    if (map->geoLayers[layerID]->type != 0) {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("��֧�ֵ�����"),
                              QString::fromLocal8Bit("��֧�ֶԵ�Ҫ��ͼ����к��ܶȷ���"), QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    emit KDEAnalyze(layerID);
}