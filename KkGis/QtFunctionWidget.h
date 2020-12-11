#pragma once

#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "GeoMap.h"
#include "GeoLayer.h"
#include <QMouseEvent>
#include <qstring.h>
#include <qplaintextedit.h>

class QtFunctionWidget : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT

public:
    QtFunctionWidget(QWidget *parent = nullptr);

    ~QtFunctionWidget() Q_DECL_OVERRIDE;

    bool isExist(GeoLayer *layer);

    bool isExist(QString fullpath);

    void strongUpdata(); //���Ÿ�����ʹ�ã�����project��update����Ӧ
    void renderLayer(GeoLayer *layer);   //���ݺ�renderer�����˱仯��ʱ�����
    void switchOpenrateMode(int operateMode);

    void setHasTableShowing(bool flag);

    GeoMap *getMap();

    void moveLayerLevel(int from, int to);

    void setOutCurrentLayer(GeoLayer *layer);

protected:
    virtual void initializeGL() Q_DECL_OVERRIDE;

    virtual void
    resizeGL(int w, int h) Q_DECL_OVERRIDE;  //����update��ʱ�򲻱�֤����resizeGL�����������project������Ҫ�ֶ�����
    virtual void paintGL() Q_DECL_OVERRIDE;

private:

    GeoMap *map;
    QOpenGLShaderProgram shaderProgram;
    QMap<GeoFeature *, QList<QOpenGLVertexArrayObject *> *> featureVaosMap;
    QMap<GeoLayer *, QList<QOpenGLBuffer *> *> layerBosMap;

    GeoLayer *currentLayer; //���浱ǰͼ�㣬��Ӱ��,������ʾ�������warning����Ҫֱ�ӸĶ�currentlayer��Ҫͨ��switchLayer�Ķ����Ա�֤map�е�currentlayer��˱���ͬ��
    //GeoLayer* tempProcessLayer; //���ڴ������ݶ������õ���תͼ��
    QList<GeoLayer *> waitLoadedLayers;

    int w;
    int h;
    QRectF worldRect;
    QRectF originWorldRect;
    bool hasSetRect;  //��ʾ�Ƿ�Ϊ��һ�λ���޵��м���
    bool hasWaH;     //���Ƿ�h��w�Ѿ���ʼ����һ��
    QMatrix4x4 view;
    QMatrix4x4 projection;
    QPoint screenPointBegin;
    QPoint screenPointDuring;
    QPoint screenPointEnd;
    float scale;
    int operateMode;
    bool hasTableShowing;

    //-------------------֮��ĺ����ᱣ֤��ȫ�ԣ����ö����ж�---------------------
    void addlayer(GeoLayer *layer);

    void changeLayer(GeoLayer *layer);

    void changeLayer(QString fullpath);   //changeָ�ı����ڽ��пռ������ͼ��
    GeoLayer *removeLayer(GeoLayer *layer);

    GeoLayer *removeLayer(QString fullpath);

    void deleteLayer(GeoLayer *layer);

    void initLayer(GeoLayer *layer);

    void initLayer(QString fullpath);

    void switchLayer(GeoLayer *layer);    //�л�currentͼ�㣬��ִ���ػ�
    void switchLayer(QString fullpath);

    void switchWorldRect(GeoLayer *layer);

    void switchWorldRect(QString fullpath);

    void switchWorldRect(GeoFeature *feature);

    void switchWorldRect(QRectF rect);        //�л���������ִ���ػ�
    //------------------------------------------------------------------------

    void setDefaultRenderColor(int dataType, int rendererType, Render *render, int geoRenderType,
                               StretchRenderer *streRenderer, float cellValue);

    void setSelectedRenderColor(Render *render, int type);

    void releaseVaos(GeoLayer *layer);

    void bindVaos(GeoLayer *layer);

    void project();   //ʹ�����細�ڽ���ͶӰ
    void loadWaitLayers();

    void refreshWorldRectForTrans(QPointF begin, QPointF end, int scaleType);

    void refreshWorldRectForScale(QPointF originScreen, float scale, int scaleType);

    void refreshWorldRectForScale(QPointF originScreen, QRectF rect, int scaleType);

    QPointF screenToWorld(QPointF screenPoint);

    QPointF screenToNormalizedPos(QPointF screenPoint);

    void initWorldRect(QRectF rect);  //��ʼ�����細�ڴ�С����֤zoom��rect����Ļ����
    int getResizeDirection(QRect oriRect, QRect newRect);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

signals:

    void changeTableSelectionSignal(GeoFeature *feature);

public slots:

    void on_addLayerData(GeoLayer *layer);

    void on_deleteLayerData(GeoLayer *layer);

    void on_zoomToLayer(GeoLayer *layer);

    void on_setSymbol(Symbol *symbol);

    void on_zoomToFeature(GeoFeature *feature);

    void on_transToFeature(GeoFeature *feature);

    void on_zoomToRect(QRectF rect);

    void on_transToRect(QRectF rect);

    void on_selectFeature(GeoFeature *feature);
};

