/*!
 * @author tau 
 * @date 12/29/20
*/

#ifndef GISL_RECTANGLE_H
#define GISL_RECTANGLE_H

#include <ogr_geometry.h>
#include <QPointF>
#include <QVector4D>
#include <QRectF>

namespace GisL {
    class Rectangle : public OGREnvelope {
    public:
        explicit Rectangle( OGREnvelope &envelope );

        void merge( Rectangle const &sOther );

        void merge( double dfX, double dfY );

        QRectF getQRectF( ) const;

        QPointF center( ) const;

        QVector4D center4D( ) const;

        float minX;
        float maxX;
        float minY;
        float maxY;

    private:
        OGREnvelope *pmEnvelope;

    };
}

#endif //GISL_RECTANGLE_H
