/*!
 * @author tau
 * @date 1/1/21
 */

#ifndef GISL_COORDINATETRANSFORM_H
#define GISL_COORDINATETRANSFORM_H

#include <QPolygon>
#include <QVector>
#include <ogr_geometry.h>

namespace gisl {

class ExchangePointXY {
public:
    ExchangePointXY(double x, double y, ExchangePointXY* next = nullptr);

    double getX() const;

    double getY() const;

    ExchangePointXY* getNext() const;

    void setNext(ExchangePointXY* xy);

private:
    double mX;
    double mY;
    ExchangePointXY* next;
};

class ExchangeLine {
public:
    ExchangeLine();

    void append(double x, double y);

    ExchangeLine* getNext() const;

    void setNext(ExchangeLine* line);

private:
    ExchangePointXY* firstPoint;
    ExchangePointXY* currentPoint;
    int pointCount;
    ExchangeLine* next;
};

class ExchangeLinearRing {
public:
    explicit ExchangeLinearRing(OGRLinearRing* p);

    //        float **pos;
    QVector<float> posVector;
    int posCount;
    QPolygonF qPolygon;
};

class ExchangePolygon {
public:
    ExchangePolygon();

    void append(ExchangeLine* p);

private:
    ExchangeLine* firstLine;
    ExchangeLine* currentLine;
    int lineCount;
    ExchangePolygon* next;
};
} // namespace gisl

#endif // GISL_COORDINATETRANSFORM_H
