#include "postgisDialog.h"
#include "ui_postgisDialog.h"

PostgisDialog::PostgisDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::postgisDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("PostGIS connection");

    //设置默认值
    ui->ePassword->setEchoMode(QLineEdit::Password);
    ui->eUsername->setText("postgres");
    ui->eServerHost->setText("localhost");
	ui->ePassword->setText("zhang002508");
    ui->eServerHost1->setText("5432");
	ui->eDatabase->setText("postgis_25_sample");
}

PostgisDialog::~PostgisDialog()
{
    delete ui;
}

QString PostgisDialog::getUsername()
{
    return ui->eUsername->text();
}

QString PostgisDialog::getPassword()
{
    return ui->ePassword->text();
}

QString PostgisDialog::getLocalhost()
{
    return ui->eServerHost->text();
}

QString PostgisDialog::getPort()
{
    return ui->eServerHost1->text();
}

QString PostgisDialog::getDatabase()
{
    return ui->eDatabase->text();
}

QString PostgisDialog::getLayername()
{
    return ui->comeLayername->currentText();
}

QString PostgisDialog::getPath()
{
	return "PG:dbname=" + dbname + " " + "host=" + host + " " + "port=" + port + " " + "user=" + user + " " + "password=" + password;
}

void PostgisDialog::on_Ok_clicked()
{
     this->accept();
}

void PostgisDialog::on_Cancel_clicked()
{
    this->close();
}

void PostgisDialog::on_pushButton_clicked()
{
//当按下按钮后连接数据库并将指定数据库中layer的名称显示到comebox中
    //注册驱动
    GDALAllRegister();
    OGRRegisterAll();

    //初始化各类指针
    OGRLayer *poLayer=nullptr;
    GDALDataset *pODS=nullptr;
    GDALDriver *pDriver=nullptr;
    pDriver=OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName("PostgreSQL");
    if(pDriver==nullptr)
    {
     qDebug()<<"can't get postgreSQL driver"<<endl;
     return;
    }

    //得到用户输入的数据
    dbname=ui->eDatabase->text();
    host=ui->eServerHost->text();
    port=ui->eServerHost1->text();
    user=ui->eUsername->text();
    password=ui->ePassword->text();

    //连接数据库
    QString path="PG:dbname="+dbname+" "+"host="+host+" "+"port="+port+" "+"user="+user+" "+"password="+password;
    const char *filePath;
    QByteArray baPath=path.toLatin1();
    filePath=baPath.data();

    pODS = (GDALDataset*)GDALOpenEx(filePath,GDAL_OF_VECTOR,NULL,NULL,NULL);
    if(pODS==nullptr)
    {
        qDebug()<<"can't open"<<filePath<<endl;
        return;
    }
    else
    {
        qDebug()<<"can open"<<filePath<<endl;
    }

    //得到图层名称并赋值给comebox
    int layerNum=pODS->GetLayerCount();
    const char* layername;
    for(int i=0;i<layerNum;i++)
    {
       layername=pODS->GetLayer(i)->GetName();
       QString layername1(layername);
       ui->comeLayername->addItem(layername1);
    }

    selectedLayer=ui->comeLayername->currentText();
   //返回用户所选的值
}
