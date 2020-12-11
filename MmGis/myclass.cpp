#include "myclass.h"

MyClass::MyClass(QWidget *parent)
        : QMainWindow(parent) {
    ui.setupUi(this);
    createActions();
    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);
    gl = new MyGLWidget();
    mywizard = new MyWizard();
    QObject::connect(this, SIGNAL(updateMyGLSignal(int,const char*, int)), gl,
                     SLOT(updateMyGLSlot(int,const char*, int)));
    QObject::connect(this,
                     SIGNAL(updateMyGLPostgresqlSignal(int, int, QString, QString, QString, QString, QString, QString)),
                     gl,
                     SLOT(updateMyGLPostgresqlSlot(int, int, QString, QString, QString, QString, QString, QString)));
    QObject::connect(this, SIGNAL(updateData(int, CGeoMap * , int, int)), gl,
                     SLOT(updateData(int, CGeoMap * , int, int)));
    QObject::connect(this, SIGNAL(updateLayerIDSignal(int, int)), gl, SLOT(updateLayerID(int, int)));
    QObject::connect(mywizard, SIGNAL(sendPostgresqlData(QString, QString, QString, QString, QString, QString)), this,
                     SLOT(getPostgresqlSlot(QString, QString, QString, QString, QString, QString)));
    QObject::connect(this, SIGNAL(sendColorAndWidthData2(int, QColor, QColor, float)), gl,
                     SLOT(getColorAndWidthData2(int, QColor, QColor, float)));
    QObject::connect(this, SIGNAL(sendColorAndWidthData(vector<QString>, QColor, QColor, float)), gl,
                     SLOT(getColorAndWidthObjs(vector<QString>, QColor, QColor, float)));
    QObject::connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(clearContent()));
    QObject::connect(this, SIGNAL(KDEAnaly(int)), gl, SLOT(KDEAnaly(int)));
    QObject::connect(this, SIGNAL(sendLayerClours(int, QString)), gl, SLOT(setLayerClours(int, QString)));

    ui.verticalLayout_2->addWidget(gl);
    //this->setWindowIcon(QIcon(":/qss_icons/rc/address.svg"));
}

MyClass::~MyClass() {
    if (gl != NULL)
        delete gl;
}


void MyClass::readGeoJson() {
    QString message = tr("readGeoJson");
    statusBar()->showMessage(message);
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("file"), "", tr("*.geojson"));
    if (!filename.isNull()) {
        const char *fileName;
        // �����ƶ�ȡ
        QByteArray ba = filename.toLocal8Bit();
        fileName = ba.data();
        FILE *file = fopen(fileName, "rb");
        if (file == NULL)//�ж��ļ�����
        {
            exit(1);
        }
        /*
        MyGLWidget *gl = new MyGLWidget();
        gl->id = gls.size(); // ����id
        // �������е�ͼ��
        gls.append(gl);
        */
        //MyGLWidget* glTemp = new MyGLWidget();
        //glTemp->map = gl->map;
        int layerID = gl->map->geoLayers.size();
        int mode = 0;
        emit updateMyGLSignal(mode, fileName, layerID);
        //gl->show();
        // ɾ�����е�
        //QLayoutItem *child;
        //while(child=ui.verticalLayout_2->takeAt(0)) {
        //delete child;
        //}
        // ����ȫ��
        //gl=glTemp;
        // �˵���

        emit updateMyTreeWidgetSignal(gl->map);
        //this->show();
    } else {
        qDebug() << "ȡ��";
    }

}

void MyClass::readShape() {
    QString message = tr("readShape");
    statusBar()->showMessage(message);
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("file"), "", tr("*.shp"));
    if (!filename.isNull()) {
        const char *fileName;
        // �����ƶ�ȡ
        QByteArray ba = filename.toLocal8Bit();
        fileName = ba.data();
        FILE *file = fopen(fileName, "rb");
        if (file == NULL)//�ж��ļ�����
        {
            exit(1);
        }
        /*
        MyGLWidget* glTemp = new MyGLWidget();
        glTemp->map = gl->map;
        int layerID = gl->map->geoLayers.size();
        QObject::connect(this,SIGNAL(updateMyGLSignal(int,const char*,int)),glTemp,SLOT(updateMyGLSlot(int,const char*,int)),Qt::UniqueConnection);
        int mode = 1;
        emit updateMyGLSignal(mode,fileName,layerID);
        // ɾ�����е�
        QLayoutItem *child;
        while(child=ui.verticalLayout_2->takeAt(0)) {
        delete child;
        }
        // ����ȫ��
        ui.verticalLayout_2->addWidget(glTemp);
        gl = glTemp;
        */
        int layerID = gl->map->geoLayers.size();
        int mode = 1;
        emit updateMyGLSignal(mode, fileName, layerID);
        // �˵���
        // QObject::connect(this,SIGNAL(updateMyTreeWidgetSignal(CGeoMap *,MyGLWidget *)),treeWidget,SLOT(updateMyTreeWidgetSlot(CGeoMap *,MyGLWidget*)),Qt::UniqueConnection);
        emit updateMyTreeWidgetSignal(gl->map);
        //this->show();
    } else {
        qDebug() << "ȡ��";
    }
}

void MyClass::getColorAndWidthData(int layerID, QColor fillColor, QColor strokeColor, float width) {
    emit sendColorAndWidthData2(layerID, fillColor, strokeColor, width);
}


void MyClass::saveShapefile() {
    QString message = tr("saveShapefile");
    statusBar()->showMessage(message);
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("file"), "", tr("*.shp"));
    if (!filename.isNull()) {
        const char *fileName;
        // �����ƶ�ȡ
        QByteArray ba = filename.toLocal8Bit();
        fileName = ba.data();
        FILE *file = fopen(fileName, "rb");
        if (file == NULL)//�ж��ļ�����
        {
            exit(1);
        }
        Connect_Sql connectSql;
        connectSql.ConnectToDBSaveShpByGdal(fileName);
        QMessageBox::information(NULL, QString::fromLocal8Bit("���������"), QString::fromLocal8Bit("�ѳɹ������shp�ļ���"),
                                 QMessageBox::Yes, QMessageBox::Yes);
    } else {
        qDebug() << "ȡ��";
    }
}

void MyClass::getDatabaseData() {
    // ��

    mywizard->show();
}

void MyClass::createActions() {
    connect(ui.actionGeojson, &QAction::triggered, this, &MyClass::readGeoJson);
    connect(ui.actionShp, &QAction::triggered, this, &MyClass::readShape);
    connect(ui.actionSave_shapefile, &QAction::triggered, this, &MyClass::saveShapefile);
    connect(ui.actionGet_databaseData, &QAction::triggered, this, &MyClass::getDatabaseData);
    //connect(ui.actionIndex_grid,&QAction::triggered,this,&MyClass::showIndexGrids);
    //connect(ui.actionHideIndexGrid,&QAction::triggered,this,&MyClass::hideIndexGrids);
}

void
MyClass::getPostgresqlSlot(QString dbname, QString host, QString user, QString password, QString table, QString port) {
    this->dbname = dbname;
    this->host = host;
    this->user = user;
    this->password = password;
    this->table = table;
    this->port = port;
    int layerID = gl->map->geoLayers.size();
    int mode = 6;
    emit updateMyGLPostgresqlSignal(mode, layerID, port, dbname, host, user, password, table); // ��ȡ���ݿ⣬������Ⱦ
    emit updateMyTreeWidgetSignal(gl->map);
    gl->update();
}

void MyClass::updateTreeGLSlot(int mode, CGeoMap *map, int layerID, int size) {
    /*
    MyGLWidget* glTemp = new MyGLWidget();
    glTemp->map = gl->map;
    //int layerID = gl->map->geoLayers.size();
    glTemp->layerID = gl->layerID;
    glTemp->viewLayer = gl->viewLayer;
    glTemp->rect = gl->rect;
    QObject::connect(this,SIGNAL(updateData(int,CGeoMap*)),glTemp,SLOT(updateData(int,CGeoMap*)),Qt::UniqueConnection);
    emit updateData(mode,map);
    // ɾ�����е�
    QLayoutItem *child;
    while(child=ui.verticalLayout_2->takeAt(0)) {
    delete child;
    }
    // ����ȫ��
    ui.verticalLayout_2->addWidget(glTemp);
    gl=glTemp;
    */
    //int layerID = gl->map->geoLayers.size();
    //int mode = 0;
    emit updateData(mode, map, layerID, size);
    //this->show();
    gl->update();
}

/*
void MyClass::paintEvent(QPaintEvent * /* event )
{
CGeoMap *map = new CGeoMap();
GeoJsonTool geo;
CGeoLayer *layer = geo.readGeoJSON("F:\\college\\������\\kmj\\second_exp\\second_exp\\test.geojson");
map->addLayer(layer);
QPainter painter(this);
// �����ܵ��������
painter.setRenderHint(QPainter::Antialiasing, true);
// ����任
int W=width(); //ȡ����Ŀ�
int H=height();//ȥ����ĸ�
// �ӿ� ����
QRect view_rect(QPoint(0,0),QPoint(W,H));
// ���� �߼�
QRect logic_rect = map->getScope().toRect();
// ʹ�ӿڱ����봰�ڱ���һ��
double ratio = -logic_rect.width()/logic_rect.height();
view_rect.setWidth(view_rect.height()*ratio);
view_rect.moveLeft((W-view_rect.width())/2);
painter.setViewport(view_rect);
painter.setWindow(logic_rect);
map->paint(&painter);

}
*/


void MyClass::updateLayerIDSlot(int mode, int layerID) {
    emit updateLayerIDSignal(mode, layerID);
    gl->update();
}

/*
void MyClass::showIndexGrids(){
gl->showIndexGrid = true;
}

void MyClass::hideIndexGrids(){
gl->showIndexGrid = false;
}
*/
void MyClass::IndexGrids() {
    gl->update();
}

void MyClass::search() {
    if (!gl->viewLayer)
        return;
    if (gl->viewLayer->getLayerName().compare("bou2_4p") != 0)
        return;
    // ���lineedit����
    QString content = ui.lineEdit->displayText();
    if (!content.isNull()) {
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        manager->setNetworkAccessible(QNetworkAccessManager::Accessible);
        QNetworkRequest qnr(QUrl("http://www.cartovision.cn/LuceneDemo/search?name=" + content));
        QNetworkReply *reply = manager->get(qnr);
        connect(manager, SIGNAL(finished(QNetworkReply * )), this, SLOT(finishHTTP(QNetworkReply * )),
                Qt::UniqueConnection);
    }
}

//�����������
void MyClass::finishHTTP(QNetworkReply *reply) {
    QString result = reply->readAll();
    vector<QString> names;
    //QString name;
    // ����result
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(result.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << parseError.error << endl;
    }
    QJsonObject jsonObject = jsonDocument.object();
    // �õ�objID
    if (jsonObject["flag"].toInt() == 1) {
        //������ʾ���
        QString info;
        //��ѯ���˽��
        for (int i = 0; i < jsonObject["resultList"].toArray().size(); i++) {
            QJsonObject resultObj = jsonObject["resultList"].toArray()[i].toObject();
            names.push_back(resultObj["name"].toString());
            int index = resultObj["id"].toString().toInt();
            double area = resultObj["area"].toString().toDouble();
            //objID.push_back(index);
            info += QString::fromLocal8Bit("��������:") + resultObj["name"].toString() +
                    QString::fromLocal8Bit(",�������:") + QString::number(area) + QString::fromLocal8Bit("��ƽ��ǧ��\n");
        }
        QMessageBox::information(NULL, QString::fromLocal8Bit("��ѯ���"), info, QMessageBox::Yes, QMessageBox::Yes);
        // �����ź�ʹobjID��ɫ
        QColor fillColor("#b97016");
        QColor strokeColor("#ca590a");
        float strokeWidth = 1.5;
        emit sendColorAndWidthData(names, fillColor, strokeColor, strokeWidth);
    } else {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("��ѯ���"), QString::fromLocal8Bit("��ѯʧ��!"),
                              QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    //�ͷ�
    reply->deleteLater();
}

void MyClass::clearContent() {
    ui.lineEdit->clear();
}

void MyClass::KDEAnalyze(int layerID) {
    emit KDEAnaly(layerID);
}

void MyClass::getLayerClours(int layerID, QString attri) {
    emit sendLayerClours(layerID, attri);
}
