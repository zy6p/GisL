#include "geopolyline.h"
#include "EnumType.h"
#include "qmath.h"

GeoPolyline::GeoPolyline() {
    this->type = EnumType::POLYLINE;
}

GeoPolyline::~GeoPolyline() {
    for (int i = 0; i < size(); i++) {
        delete pts.at(i);
    }
}

void GeoPolyline::addPoint(GeoPoint *point) {
    pts.push_back(point);
}

GeoPoint *GeoPolyline::getPointAt(int idx) {
    return pts.at(idx);
}

GeoPoint *GeoPolyline::removeAt(int idx) {
    GeoPoint *p = pts.at(idx);
    pts.removeAt(idx);
    return p;
}

QList<GeoPoint *> GeoPolyline::removeAll() {
    pts.clear();
    return pts;
}

int GeoPolyline::size() {
    return pts.size();
}

QRectF GeoPolyline::getRect() {
    GeoPoint *firstPoint = getPointAt(0);
    float left = firstPoint->getXf();
    float top = firstPoint->getYf();
    float right = firstPoint->getXf();
    float bottom = firstPoint->getYf();
    for (int i = 0; i < size(); i++) {
        GeoPoint *p = getPointAt(i);
        if (p->getXf() < left) left = p->getXf();
        if (p->getYf() > top) top = p->getYf();
        if (p->getXf() > right) right = p->getXf();
        if (p->getYf() < bottom) bottom = p->getYf();
    }
    return QRectF(QPointF(left, top), QPointF(right, bottom));
}

double GeoPolyline::disToPoint(GeoPoint *pt) {
    double x1, y1, x2, y2;
    double x0 = pt->getXf();
    double y0 = pt->getYf();
    double mindis, dis, dis1, dis2;

    for (int i = 0; i < size() - 1; i++) {
        x1 = pts.at(i)->getXf();
        y1 = pts.at(i)->getYf();
        x2 = pts.at(i + 1)->getXf();
        y2 = pts.at(i + 1)->getYf();

        //���ÿһ���߶ε���С��Ӿ���
        double top = qMax(y1, y2);
        double left = qMin(x1, x2);
        double bottom = qMin(y1, y2);
        double right = qMax(x1, x2);
        QRectF segmentRect = QRectF(QPointF(left, top), QPointF(right, bottom));
        //��ô�����ֱ�ߵĽ���
        double A = (y1 - y2) / (x1 - x2);
        double B = y1 - A * y1;
        double m = x0 + A * y0;
        QPointF ptCorss;
        ptCorss.setX((m - A * B) / (A * A + 1));
        ptCorss.setY(A * ptCorss.x() + B);

        if (segmentRect.contains(ptCorss))//�����������С��Ӿ���֮��ȡ���߾���
        {
            dis = qAbs(((x0 - x1) * (y2 - y1) + (y0 - y1) * (x1 - x2))) / pow(pow(y2 - y1, 2) + pow(x1 - x2, 2), 0.5);
        } else//����ȡ�������˵�����ľ���
        {
            dis1 = pts.at(i)->disToPoint(pt);
            dis2 = pts.at(i + 1)->disToPoint(pt);
            dis = qMin(dis1, dis2);
        }


        if (i == 0)
            mindis = dis;
        else
            mindis = qMin(mindis, dis);
    }
    return mindis;
}

GeoPoint *GeoPolyline::getMeanCenter() {
    double meanX, meanY;
    double sumX = 0, sumY = 0;
    int n = this->size();
    for (int i = 0; i < n; i++) {
        sumX = sumX + pts.at(i)->getXf();
        sumY = sumY + pts.at(i)->getYf();
    }
    meanX = sumX / n;
    meanY = sumY / n;
    GeoPoint *pt = new GeoPoint();
    pt->setXf(meanX);
    pt->setYf(meanY);
    return pt;
}


