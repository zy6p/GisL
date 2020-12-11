#include "GeoLayer.h"
#include "EnumType.h"
#include "util.h"

GeoLayer::GeoLayer() : render(NULL), visibility(true), selectMode(EnumType::selectMode::SINGLEMODE),
                       dataChangeType(EnumType::dataChangedType::NOCHANGEDATA),
                       indexMode(EnumType::indexMode::QUADTREE), type(-1),
                       globalDefaultColomn("NAME") {

}

GeoLayer::~GeoLayer() {
    for (int i = 0; i < size(); i++) {
        delete features.at(i);
    }
    if (render) {
        delete render;
    }
}

GeoFeature *GeoLayer::getFeatureAt(int i) {
    return features.at(i);
}

QList<GeoFeature *> GeoLayer::getAllFeature() {
    return features;
}

void GeoLayer::addFeature(GeoFeature *feature) {
    features.push_back(feature);
}

GeoFeature *GeoLayer::removeFeatureAt(int idx) {
    GeoFeature *obj = features.at(idx);
    features.removeAt(idx);
    return obj;
}

QList<GeoFeature *> GeoLayer::removeAll() {
    QList<GeoFeature *> copyList = features;
    features.clear();
    return copyList;
}

Render *GeoLayer::setRender(Render *newRender) {
    Render *oldRender = NULL;
    if (this->render) {
        oldRender = this->render;
    }
    this->render = newRender;
    return oldRender;
}

Render *GeoLayer::getRender() {
    return this->render;
}

int GeoLayer::size() {
    return features.size();
}

void GeoLayer::setType(int type) {
    this->type = type;
}

int GeoLayer::getType() {
    return type;
}

QString GeoLayer::getName() {
    return name;
}

void GeoLayer::setName(QString name) {
    this->name = name;
}

QString GeoLayer::getTypeString() {
    if (type == EnumType::POINT) {
        return "Point";
    } else if (type == EnumType::POLYLINE) {
        return "Polyline";
    } else if (type == EnumType::POLYGON) {
        return "Polygon";
    }
    return "Non_Such_Type";
}

//由于QTCreater不是采用定时编译，也就不能实时地告知编写错误，也不能对没有编译的变量进行提示，如果想要自动提示新添加的变量，就需要进行一次编译

void GeoLayer::bindDefaultRender() {
    if (render) {
        delete render;
    }
    Render *render = new Render();
    LineSymbol *lineSymbol = new LineSymbol();
    LineSymbol *markerOutlineSymbol = new LineSymbol();
    LineSymbol *fillOutlineSymbol = new LineSymbol();
    MarkerSymbol *markerSymbol = new MarkerSymbol();
    FillSymbol *fillSymbol = new FillSymbol();
    QColor black;
    QColor white;
    QColor red;
    QColor blue;
    QColor yellow;
    QColor EEEEEE;
    black.setNamedColor("black");
    white.setNamedColor("white");
    red.setNamedColor("red");
    blue.setNamedColor("blue");
    yellow.setNamedColor("yellow");
    EEEEEE.setNamedColor("#EEEEEE");
    lineSymbol->setWidth(1.5);   //线宽默认为1.5
    lineSymbol->setColor(black);
    markerOutlineSymbol->setWidth(1);
    markerOutlineSymbol->setColor(black);
    fillOutlineSymbol->setWidth(1);
    fillOutlineSymbol->setColor(black);
    markerSymbol->setColor(red);
    markerSymbol->setSize(8);  //点的size默认为8
    markerSymbol->setOutline(markerOutlineSymbol);
    fillSymbol->setColor(EEEEEE);
    fillSymbol->setOutline(fillOutlineSymbol);

    render->setMarkerSymbol(markerSymbol);
    render->setFillSymbol(fillSymbol);
    render->setLineSymbol(lineSymbol);
    this->render = render;

    //绑定stretchRenderer
    StretchRenderer *renderer = new StretchRenderer();
    renderer->addColor(blue);
    renderer->addColor(red);
    stretchRenderer = renderer;
}

void GeoLayer::setSource(int source) {
    this->source = source;
}

int GeoLayer::getSource() {
    return this->source;
}

QString GeoLayer::getSourceName() {
    if (this->source == EnumType::source::GEOJSON) return "GeoJson";
    else if (this->source == EnumType::source::SHAPEFILE) return "ShapeFile";
    else if (this->source == EnumType::source::POSTGRESQL) return "PostgreSql";
    else if (this->source == EnumType::source::GEOTIFF) return "GEOTIFF";
    else return "Unknown Type";
}

void GeoLayer::setAttributeNames(QList<QString> names) {
    layerAttributeNames = names;
}

QList<QString> GeoLayer::getAttributeNames() {
    return layerAttributeNames;
}

void GeoLayer::setSelectMode(int mode) {
    this->selectMode = mode;
}

int GeoLayer::getSelectMode() {
    return selectMode;
}

void GeoLayer::setDataChangedType(int type) {
    dataChangeType = type;
}

int GeoLayer::getDataChangedType() {
    return dataChangeType;
}

GeoFeature *GeoLayer::identify(GeoPoint *point, float threshold) {
    return util::identify(point, this, threshold, spatialIndex);
}

QList<GeoFeature *> GeoLayer::search(QString attriName, QString attriValue) {
    return util::search(this, attriName, attriValue);
}

QList<QString> GeoLayer::getAttriNames(GeoLayer *layer) {
    return QList<QString>();
}

void GeoLayer::setSelectionColor(QColor color) {
    render->configSelection(color);
}

void GeoLayer::setSelectionWidth(float width) {
    render->configSelection(width);
}

void GeoLayer::setSelectionconfiguration(QColor color, float width) {
    render->configSelection(color, width);
}

//根据不同的模式选取要素，同时将被选取的要素放到list顶部，便于最后绘制
void GeoLayer::selectFeature(GeoFeature *feature) {
    if (selectMode == EnumType::selectMode::SINGLEMODE) {
        if (features.contains(feature)) {
            if (selectedFeatures.size()) {
                selectedFeatures.clear();
            }
            selectedFeatures.push_back(feature);
            moveFeatureToTop(feature);
        }
    } else if (selectMode == EnumType::selectMode::MULTIMODE) {
        if (features.contains(feature)) {  //判断是否为本layer要素
            if (!selectedFeatures.contains(feature)) {
                selectedFeatures.push_back(feature);
                moveFeatureToTop(feature);
            }
        }
    }
}

QList<GeoFeature *> GeoLayer::getSelectedFeatures() {
    return selectedFeatures;
}

bool GeoLayer::hasSelected(GeoFeature *feature) {
    if (selectedFeatures.contains(feature)) {
        return true;
    }
    return false;
}

void GeoLayer::clearSelections() {
    selectedFeatures.clear();
}

void GeoLayer::moveFeatureToTop(GeoFeature *feature) {
    if (features.contains(feature)) {
        features.move(features.indexOf(feature), features.size() - 1);  //将选取的要素最后绘制，解决压盖问题
    }
}

void GeoLayer::setIndexMode(int mode) {
    indexMode = mode;
}

int GeoLayer::getIndexMode() {
    return indexMode;
}

void GeoLayer::setIndex(Index *index) {
    this->spatialIndex = index;
}

Index *GeoLayer::getIndex() {
    return this->spatialIndex;
}

void GeoLayer::setSpatialIndex(Index *idx) {
    spatialIndex = idx;
}

QString GeoLayer::getGlobalDefaultColomn() {
    return globalDefaultColomn;
}

void GeoLayer::setGelbalDefaultColomn(QString def) {
    globalDefaultColomn = def;
}

StretchRenderer *GeoLayer::getStretchRenderer() {
    return this->stretchRenderer;
}

void GeoLayer::setStretchRenderer(StretchRenderer *renderer) {
    this->stretchRenderer = renderer;
}

int GeoLayer::getDataType() {
    return dataType;
}

void GeoLayer::setDataType(int type) {
    dataType = type;
}

int GeoLayer::getRendererType() {
    return rendererType;
}

void GeoLayer::setRendererType(int type) {
    rendererType = type;
}

QString GeoLayer::getAttriToStretch() {
    return attriToStretch;
}

void GeoLayer::setAttriToStretch(QString attri) {
    attriToStretch = attri;
}

QRectF GeoLayer::getRect() {
    if (!size()) {
        return QRectF(0, 0, 0, 0);   //无效结果
    }
    float left, top, right, bottom;
    if (type == EnumType::POINT) {  //点图层point
        GeoPoint *firstPoint = (GeoPoint *) (features.at(0)->getGeometry());
        left = firstPoint->getXf();
        top = firstPoint->getYf();
        right = firstPoint->getXf();
        bottom = firstPoint->getYf();

        for (int i = 0; i < size(); i++) {
            GeoPoint *p = (GeoPoint *) features.at(i)->getGeometry();
            if (p->getXf() < left) left = p->getXf();
            if (p->getYf() > top) top = p->getYf();
            if (p->getXf() > right) right = p->getXf();
            if (p->getYf() < bottom) bottom = p->getYf();
        }
    } else if (type == EnumType::POLYLINE) { //线图层polyline
        GeoPolyline *firstPolyline = (GeoPolyline *) (features.at(0)->getGeometry());
        GeoPoint *firstPoint = firstPolyline->getPointAt(0);
        left = firstPoint->getXf();
        top = firstPoint->getYf();
        right = firstPoint->getXf();
        bottom = firstPoint->getYf();

        for (int i = 0; i < size(); i++) {
            QRectF rect = ((GeoPolyline *) features.at(i)->getGeometry())->getRect();
            if (rect.left() < left) left = rect.left();
            if (rect.top() > top) top = rect.top();
            if (rect.right() > right) right = rect.right();
            if (rect.bottom() < bottom) bottom = rect.bottom();
        }
    } else if (type == EnumType::POLYGON) { //面图层polygon
        GeoPolygon *firstPolyline = (GeoPolygon *) features.at(0)->getGeometry();
        GeoPoint *firstPoint = firstPolyline->getPointAt(0);
        left = firstPoint->getXf();
        top = firstPoint->getYf();
        right = firstPoint->getXf();
        bottom = firstPoint->getYf();

        for (int i = 0; i < size(); i++) {
            QRectF rect = ((GeoPolygon *) features.at(i)->getGeometry())->getRect();
            if (rect.left() < left) left = rect.left();
            if (rect.top() > top) top = rect.top();
            if (rect.right() > right) right = rect.right();
            if (rect.bottom() < bottom) bottom = rect.bottom();
        }
    }
    return QRectF(QPointF(left, top), QPointF(right, bottom));
}

bool GeoLayer::isVisable() {
    return this->visibility;
}

void GeoLayer::setVisable(bool visibility) {
    this->visibility = visibility;
}

QString GeoLayer::getFullPath() {
    return this->fullpath;
}

void GeoLayer::setFullPath(QString fullpath) {
    this->fullpath = fullpath;
}
