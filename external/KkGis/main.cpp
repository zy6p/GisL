#include <QApplication>
#include <QTextCodec>
#include <qsurfaceformat.h>
#include "QtFunctionWidget.h"
#include <QVBoxLayout>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
	MainWindow w;
	w.setWindowTitle("mainWindow");

	QFile f("qdarkstyle/styleLight1.qss");
	if (!f.exists())
	{
		printf("Unable to set stylesheet, file not found\n");
	}
	else
	{
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		qApp->setStyleSheet(ts.readAll());
	}

	w.show();
    return a.exec();
}
