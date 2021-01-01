/*!
 * @author tau 
 * @date 1/1/21
*/

#include "coordinatetransform.h"

GisL::ExchangePointXY::ExchangePointXY( double x, double y, ExchangePointXY *next ) : mX( x ), mY( y ), next( next ) {

}

double GisL::ExchangePointXY::getX( ) const {
    return mX;
}

double GisL::ExchangePointXY::getY( ) const {
    return mY;
}

GisL::ExchangePointXY *GisL::ExchangePointXY::getNext( ) const {
    return next;
}

void GisL::ExchangePointXY::setNext( GisL::ExchangePointXY *xy ) {
    this->next = xy;
}

GisL::ExchangeLine::ExchangeLine( ) {
    firstPoint = nullptr;
    currentPoint = firstPoint;
    pointCount = 0;
    next = nullptr;
}

void GisL::ExchangeLine::append( double x, double y ) {
    auto *p = new ExchangePointXY( x, y );
    if ( nullptr == firstPoint ) {
        firstPoint = p;
    } else {
        currentPoint->setNext( p );
    }
    currentPoint = p;
    pointCount++;
}

GisL::ExchangeLine *GisL::ExchangeLine::getNext( ) const {
    return next;
}

void GisL::ExchangeLine::setNext( GisL::ExchangeLine *line ) {
    ExchangeLine::next = line;
}

GisL::ExchangePolygon::ExchangePolygon( ) {
    firstLine = nullptr;
    currentLine = firstLine;
    lineCount = 0;
    next = nullptr;
}

void GisL::ExchangePolygon::append( GisL::ExchangeLine *p ) {
    if ( nullptr == firstLine ) {
        firstLine = p;
        currentLine = p;
    }
    currentLine->setNext( p );
    currentLine = p;
    lineCount++;
}
