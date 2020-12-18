//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOPOINT_H
#define GISL_GEOPOINT_H

#include "geofeature.h"

namespace GisL {

    class GeoPoint : public GeoFeature {
    public:
        GeoPoint();

        GeoPoint(double x, double y);

        GeoPoint(double x, double y, double z);

        ~GeoPoint();

        [[nodiscard]] double getX() const;

        void setX(double x);

        [[nodiscard]] double getY() const;

        void setY(double y);

        [[nodiscard]] double getZ() const;

        void setZ(double z);

    private:
        double x;
        double y;
        double z;

    };

}

#endif //GISL_GEOPOINT_H
