#include "myclass.h"
#include <QtWidgets/QApplication>
#include "MyGLWidget.h"
#include "MyTreeWidget.h"
#include "dialog.h"
#include "XColorMaster.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // set stylesheet
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists()) {
        printf("Unable to set stylesheet, file not found\n");
    } else {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
    MyClass *w = new MyClass();
    //MyGLWidget *glWidget=new MyGLWidget();
    //w.putOpenGLWidget(glWidget);
    MyTreeWidget *treeWidget = new MyTreeWidget();
    ///MyGLWidget *gl = new MyGLWidget();
    treeWidget->resize(231, 644);
    //w->treeWidget = treeWidget;
    //w->gl = gl;
    //treeWidget->gl = gl;
    //w.putTreeWidget(treeWidget);
    w->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QObject::connect(treeWidget, SIGNAL(updateTreeGLSignal(int, CGeoMap * , int, int)), w,
                     SLOT(updateTreeGLSlot(int, CGeoMap * , int, int)), Qt::UniqueConnection);
    QObject::connect(w, SIGNAL(updateMyTreeWidgetSignal(CGeoMap * )), treeWidget,
                     SLOT(updateMyTreeWidgetSlot(CGeoMap * )), Qt::UniqueConnection);
    QObject::connect(treeWidget, SIGNAL(updateLayerIDSignal(int, int)), w, SLOT(updateLayerIDSlot(int, int)),
                     Qt::UniqueConnection);
    QObject::connect(treeWidget, SIGNAL(sendColorAndWidthData(int, QColor, QColor, float)), w,
                     SLOT(getColorAndWidthData(int, QColor, QColor, float)), Qt::UniqueConnection);
    QObject::connect(treeWidget, SIGNAL(IndexGrids()), w, SLOT(IndexGrids()), Qt::UniqueConnection);
    QObject::connect(treeWidget, SIGNAL(KDEAnalyze(int)), w, SLOT(KDEAnalyze(int)), Qt::UniqueConnection);
    QObject::connect(treeWidget, SIGNAL(setLayerCol(int, QString)), w, SLOT(getLayerClours(int, QString)),
                     Qt::UniqueConnection);

    w->show();
    treeWidget->show();
    //MyGLWidget gl;
    //gl.show();

    return app.exec();
}
