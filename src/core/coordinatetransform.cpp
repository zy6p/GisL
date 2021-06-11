/*!
 * @author tau
 * @date 1/1/21
 */

#include "coordinatetransform.h"
#include <QDebug>

gisl::ExchangePointXY::ExchangePointXY(
    double x,
    double y,
    ExchangePointXY* next)
    : mX(x), mY(y), next(next) {}

double gisl::ExchangePointXY::getX() const {
    return mX;
}

double gisl::ExchangePointXY::getY() const {
    return mY;
}

gisl::ExchangePointXY* gisl::ExchangePointXY::getNext() const {
    return next;
}

void gisl::ExchangePointXY::setNext(gisl::ExchangePointXY* xy) {
    this->next = xy;
}

gisl::ExchangeLine::ExchangeLine() {
    firstPoint = nullptr;
    currentPoint = firstPoint;
    pointCount = 0;
    next = nullptr;
}

void gisl::ExchangeLine::append(double x, double y) {
    auto* p = new ExchangePointXY(x, y);
    if (nullptr == firstPoint) {
        firstPoint = p;
    } else {
        currentPoint->setNext(p);
    }
    currentPoint = p;
    pointCount++;
}

gisl::ExchangeLine* gisl::ExchangeLine::getNext() const {
    return next;
}

void gisl::ExchangeLine::setNext(gisl::ExchangeLine* line) {
    ExchangeLine::next = line;
}

gisl::ExchangePolygon::ExchangePolygon() {
    firstLine = nullptr;
    currentLine = firstLine;
    lineCount = 0;
    next = nullptr;
}

void gisl::ExchangePolygon::append(gisl::ExchangeLine* p) {
    if (nullptr == firstLine) {
        firstLine = p;
        currentLine = p;
    }
    currentLine->setNext(p);
    currentLine = p;
    lineCount++;
}

gisl::ExchangeLinearRing::ExchangeLinearRing(OGRLinearRing* p) {
    posCount = 0;
    for (auto point : p) {
        posCount++;
    }
    posVector.resize(2 * posCount);
    qPolygon.resize(posCount);
    int i = 0;
    for (const auto& point : p) {
        posVector[2 * i] = (float)point.getX();
        posVector[2 * i + 1] = (float)point.getY();
        qPolygon[i].setX(point.getX());
        qPolygon[i].setY(point.getY());
        //        qDebug("%d: %d , %d", i, qPolygon[i].x(), qPolygon[i].y());
        //        qPolygon.translate(100, 100);
        //        qDebug("%d: %d , %d", i, qPolygon[i].x(), qPolygon[i].y());
        //        posVector[2 * i] = (( float ) point.getY() - 29 ) / 4;
        //        posVector[2 * i + 1] = (( float ) point.getX() - 108 ) / 8;
        i++;
    }
    //    posVector.append(p->getY(0) - 29);
    //    posVector.append(p->getY(0) - 108);
    //    for ( int j = 0; j < posCount; ++j ) {
    //        qDebug("%d : %f, %f\n", i, posVector[2 * i], posVector[2 * i + 1]);
    //    }
    //    posCount++;
    //    pos = new float*[posCount];
    //    int i = 0;
    //    for ( const auto& point : p ) {
    //        pos[i] = new float[2];
    //        pos[i][0] = (float)point.getX();
    //        pos[i][1] = (float)point.getY();
    //    }
}
