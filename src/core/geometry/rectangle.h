/*!
 * @author tau 
 * @date 12/29/20
*/

#ifndef GISL_RECTANGLE_H
#define GISL_RECTANGLE_H

#include <gdal/ogr_geometry.h>

//#include "geompolygon.h"

namespace GisL {
    class Rectangle : public OGREnvelope {
    public:
        explicit Rectangle( OGREnvelope &envelope );

        void merge( Rectangle const &sOther );

        void merge( double dfX, double dfY );

        float minX;
        float maxX;
        float minY;
        float maxY;

    private:
        OGREnvelope *pmEnvelope;

    };
}

#endif //GISL_RECTANGLE_H
