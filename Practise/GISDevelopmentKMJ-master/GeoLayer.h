#ifndef GEOLAYER_H
#define GEOLAYER_H

#include <QList>
#include <QtNetwork/qnetworkrequest.h>
#include<QtNetwork/qnetworkreply.h>
#include<QtNetwork/qnetworkaccessmanager.h>
#include "Render.h"
#include "EnumType.h"
#include "GeoGeometry.h"
#include "GeoFeature.h"

#include "GridIndex.h"
#include "QuadTree.h"
#include "Practise/GISDevelopmentKMJ-master/gpc/gpc.h"
#include "StretchRenderer.h"

class GeoLayer {
public:
    GeoLayer();

    ~GeoLayer();

    GeoFeature *getFeatureAt(int i);

    QList<GeoFeature *> getAllFeature();

    void addFeature(GeoFeature *feature);

    GeoFeature *removeFeatureAt(int idx);

    QList<GeoFeature *> removeAll();

    Render *setRender(Render *render);

    Render *getRender();

    int size();

    void setType(int type);

    int getType();

    QString getName();

    void setName(QString name);

    QString getTypeString();

    QRectF getRect();

    bool isVisable();

    void setVisable(bool visibility);

    QString getFullPath();

    void setFullPath(QString fullpath);

    void setSource(int source);

    int getSource();

    QString getSourceName();

    QList<QString> getAttributeNames();

    void setSelectMode(int mode);

    int getSelectMode();

    void setDataChangedType(int type);

    int getDataChangedType();

    void bindDefaultRender();

    void setAttributeNames(QList<QString> names);

    void setIndexMode(int mode);

    int getIndexMode();

    void setIndex(Index *index);

    Index *getIndex();

    void setSpatialIndex(Index *idx);

    QString getGlobalDefaultColomn();

    void setGelbalDefaultColomn(QString def);

    StretchRenderer *getStretchRenderer();

    void setStretchRenderer(StretchRenderer *renderer);


    int getDataType();

    void setDataType(int type);

    int getRendererType();

    void setRendererType(int type);

    QString getAttriToStretch();

    void setAttriToStretch(QString attri);

//��ռ��ѯ��صģ�
    //ʶ��
    GeoFeature *identify(GeoPoint *point, float threshold);

    //��ѯ
    QList<GeoFeature *> search(QString attriName, QString attriValue);

    QList<QString> getAttriNames(GeoLayer *layer);

    void setSelectionColor(QColor color);  //���е�Ҫ��ʹ��ͬ��ɫ�����߿��������
    void setSelectionWidth(float width);

    void setSelectionconfiguration(QColor color, float width);

    void selectFeature(GeoFeature *feature);

    QList<GeoFeature *> getSelectedFeatures();

    bool hasSelected(GeoFeature *feature);

    void clearSelections();

    void moveFeatureToTop(GeoFeature *feature);

private:
    Render *render;
    StretchRenderer *stretchRenderer;
    QString name;
    QString fullpath;
    bool visibility;
    int type;   //һ��ֻ�����һ������
    QList<GeoFeature *> features;
    int source;  //��ʾ���ݵ�����url
    QList<QString> layerAttributeNames;  //�������б���ʱ���table�Ĺ���
    QList<GeoFeature *> selectedFeatures;
    int selectMode;
    int dataChangeType;
    int indexMode;//����ģʽ
    Index *spatialIndex;
    QString globalDefaultColomn; //ʹ��NAME��Ϊȫ�ּ�����Ĭ������

    int dataType;  //��ʾ��դ�����ݻ���ʸ�����ݣ��պ�����,�����դ�����������
    int rendererType;  //��ʾ�ǵ�ɫ��Ⱦ���Ƕ�ɫ��Ⱦ���պ����ã������ʸ����դ��renderer����
    QString attriToStretch;
};

#endif // GEOLAYER_H
