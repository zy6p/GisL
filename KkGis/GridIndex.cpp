#include "GridIndex.h"

GridIndex::GridIndex() {
    this->type = EnumType::indexMode::GRIDINDEX;
}

GridIndex::~GridIndex() {
    for (int i = 0; i < grids.size(); i++)
        delete grids.at(i);

}


void GridIndex::setGrid(QRectF layerRect, QList<GeoFeature *> features) {
    int featureNum = features.size();
    double dx, dy;//�����ĳ��Ϳ�

    double startx = layerRect.left();
    double starty = layerRect.top();

    dx = abs(layerRect.width() / row);
    dy = abs(layerRect.height() / col);

    double top, left, bottom, right;

    for (int j = 0; j < row; j++) {
        top = starty - dy * j;
        bottom = top - dy;
        for (int i = 0; i < col; i++) {
            left = startx + dx * i;
            right = left + dx;

            Grid *grid = new Grid();
            //����ÿ�����ӵķ�Χ����
            QRectF gridRect = QRectF(QPointF(left, top), QPointF(right, bottom));
            grid->setGridRect(gridRect);
            //��ÿ�����ӱ���ÿ��Ҫ�أ����������ཻ��Ҫ��
            for (int k = 0; k < featureNum; k++) {
                QRectF featureRect = features.at(k)->getGeometry()->getRect();
                if (featureRect.intersects(gridRect))
                    grid->addFeatures(features.at(k));
            }
            grids.append(grid);
        }
    }
}

int GridIndex::getGridNum() {
    return grids.size();
}

QList<Grid *> GridIndex::getGridsAll() {
    return grids;
}

Grid *GridIndex::getGridAt(int i) {
    return grids.at(i);
}

GeoFeature *GridIndex::searchGrid(GeoPoint *point, float thresholed) {
    int gridNum = grids.size();

    //�ҵ���������ĸ���
    Grid *gridFound;
    for (int i = 0; i < gridNum; i++)//�������и���
    {
        QRectF gridRect = grids.at(i)->getGridRect();//�õ������ľ��η�Χ
        if (gridRect.contains(QPointF(point->getXf(), point->getYf())))//�жϵ��Ƿ����ڸ���������
        {
            gridFound = grids.at(i);
            break;//ÿ�����β��ཻ���ҵ�������ѭ��
        }
    }

    //�ҵ������е����Ҫ��
    GeoFeature *featureFound;
    int featureNum = gridFound->getFeatureNum();
    QList<GeoFeature *> features = gridFound->getFeatureAll();
    for (int i = 0; i < featureNum; i++)//��������Ҫ��
    {
        GeoFeature *feature = features.at(i);//��ÿһ��Ҫ���ж��Ƿ���point�Ļ������ཻ
        GeoGeometry *geometry = feature->getGeometry();
        //�������ĵ���Ҫ�ص�С��һ���ľ�����ֵ���򷵻ظõ�
        if (geometry->getType() == EnumType::POINT) {
            GeoPoint *pt = static_cast<GeoPoint *>(geometry);
            if (pt->disToPoint(point) < thresholed)//����㵽Ҫ�ص�ľ���С�ھ�����ֵ���ҵ���Ҫ��
                featureFound = feature;
        } else if (geometry->getType() == EnumType::POLYLINE) {
            GeoPolyline *polyline = static_cast<GeoPolyline *>(geometry);
            if (polyline->disToPoint(point) < thresholed)//����㵽Ҫ���ߵľ���С�ھ�����ֵ���ҵ���Ҫ��
                featureFound = feature;
        }
            //�������ĵ��ڶ�������򷵻ظö����
        else if (geometry->getType() == EnumType::POLYGON) {
            GeoPolygon *polygon = static_cast<GeoPolygon *>(geometry);
            QVector<QPointF> polygonPoints;
            int pointNum = polygon->size();
            for (int j = 0; j < pointNum; j++)//�����ݴ洢ΪQpolygon���õ���ʽ
            {
                QPointF pt;
                pt.setX(polygon->getPointAt(j)->getXf());
                pt.setY(polygon->getPointAt(j)->getYf());
                polygonPoints.append(pt);
            }
            if (QPolygonF(polygonPoints).contains(QPointF(point->getXf(), point->getYf())))//���������ڶ�����ڣ��ҵ���Ҫ��
                featureFound = feature;
        } else {
            featureFound = NULL;
        }
    }
    return featureFound;
}

