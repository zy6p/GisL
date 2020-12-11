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
#include "gpc/gpc.h"
#include "StretchRenderer.h"

class GeoLayer
{
public:
    GeoLayer();
	~GeoLayer();
	GeoFeature* getFeatureAt(int i);
	QList<GeoFeature*> getAllFeature();
	void addFeature(GeoFeature* feature);
	GeoFeature* removeFeatureAt(int idx);
	QList<GeoFeature*> removeAll();
	Render* setRender(Render* render);
	Render* getRender();
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
	void setIndex(Index* index);
	Index* getIndex();
	void setSpatialIndex(Index *idx);
	QString getGlobalDefaultColomn();
	void setGelbalDefaultColomn(QString def);
	StretchRenderer* getStretchRenderer();
	void setStretchRenderer(StretchRenderer* renderer);


	int getDataType();
	void setDataType(int type);
	int getRendererType();
	void setRendererType(int type);
	QString getAttriToStretch();
	void setAttriToStretch(QString attri);
	
//与空间查询相关的：
	//识别
	GeoFeature *identify(GeoPoint *point, float threshold);
	//查询
	QList<GeoFeature*> search(QString attriName, QString attriValue);
	QList<QString> getAttriNames(GeoLayer *layer);

	void setSelectionColor(QColor color);  //所有的要素使用同种色彩与线宽进行配置
	void setSelectionWidth(float width);
	void setSelectionconfiguration(QColor color,float width);
	void selectFeature(GeoFeature* feature);
	QList<GeoFeature*> getSelectedFeatures();
	bool hasSelected(GeoFeature* feature);
	void clearSelections();
	void moveFeatureToTop(GeoFeature* feature);
private:
	Render* render;
	StretchRenderer* stretchRenderer;
	QString name;
	QString fullpath;
	bool visibility;
	int type;   //一层只能添加一种数据
    QList<GeoFeature*> features;
	int source;  //显示数据的完整url
	QList<QString> layerAttributeNames;  //属性名列表，暂时替代table的功能
	QList<GeoFeature*> selectedFeatures;
	int selectMode;
	int dataChangeType;
	int indexMode;//索引模式
	Index *spatialIndex;
	QString globalDefaultColomn; //使用NAME作为全局检索的默认属性

	int dataType;  //表示是栅格数据还是矢量数据，凑合用下,后可用栅格数据类代替
	int rendererType;  //表示是单色渲染还是多色渲染，凑合着用，后可用矢量与栅格renderer代替
	QString attriToStretch;
};

#endif // GEOLAYER_H
