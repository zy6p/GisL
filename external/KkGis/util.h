#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QWidget>
#include "GeoLayer.h"
#include <qopenglfunctions.h>
#include "LineSymbol.h"
#include "MarkerSymbol.h"
#include "FillSymbol.h"
#include "qcolor.h"
#include "gpc/gpc.h"
#include"ogrsf_frmts.h"

#include"Index.h"
#include"GridIndex.h"
#include"QuadTree.h"
#include "GeoMap.h"

class util {
public:
    util();

    static QString util::openFileDialog(QWidget *widget, QString curPath);

    static GeoLayer *openGeoJson(QString path);

    static GeoLayer *openGeoJsonByCJson(QString path);

    static GeoLayer *openShapeFile(QString path);

    static GeoLayer *openFileFromPostgresql(QString path, QString layername);

    static MarkerSymbol *parseSLD_Marker(QString path);

    static LineSymbol *parseSLD_Line(QString path);

    static FillSymbol *parseSLD_Fill(QString path);

    static QColor color24BitTo256(QString color);

    //static std::vector<unsigned char> hexToBin(const std::string &hex);
    //static QByteArray hexToBinInQt(QString hex);
    //static QByteArray setDefaultAlpha(QByteArray color);
    static QColor parseColor(QString hexNamedColor);  //使用qcolor方便很多，不用自己解析了
    static void tesselation(GeoPolygon *polygon, gpc_tristrip *tristrip);

    static QList<GeoFeature *> search(GeoLayer *layer, QString attriName, QString attriValue);

    static GeoFeature *identify(GeoPoint *point, GeoLayer *layer, float threshold, Index *spatialIndex);

    static QList<GeoFeature *> globalSearch(GeoMap *map, QString attriValue);

    static GeoLayer *util::grid2FeatureLayer(float **gridData, QRectF mbr, int widthNum, int heightNum,
                                             float cellSize, QString fullPath, QString name,
                                             QString cellValueAttriName);
};

#endif // UTIL_H
