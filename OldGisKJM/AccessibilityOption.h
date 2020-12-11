#pragma once

#include "COption.h"
#include "GeoPoint.h"
#include "GeoLayer.h"
#include "Option.h"

class AccessibilityOption : public Option {
public:
    AccessibilityOption();

    ~AccessibilityOption();

    void setOriLayer(GeoLayer *point);

    GeoLayer *getOriginPointLayer();

    void setDirPointLayer(GeoLayer *layer);

    GeoLayer *getDirPointLayer();

    void setArcLayer(GeoLayer *layer);

    GeoLayer *getArcLayer();

    void setNodeLayer(GeoLayer *layer);

    GeoLayer *getNodeLayer();

    QString getSaveField();

    void setSaveField(QString field);

    void setTimeLimit(float time);

    float getTimeLimit();

    bool getUseSelectedFeatures();

    void setUseSelectedFeatures(bool flag);

private:
    GeoLayer *oriPointLayer;   //od�ɱ��ĳ�����ͼ�㣬Ҳ�Ǽ���ɴ��Եĵ����ڵ�ͼ��
    GeoLayer *dirPointLayer;  //od�ɱ��ĵ����ͼ��
    GeoLayer *arcLayer;   //��·�߱�
    GeoLayer *nodeLayer;  //��·�ڵ��
    QString saveField;
    float timeLimit;  //ʱ��ɱ�����ʱ����ɾ���ɱ�
    bool useSelectedFeatures;
};

