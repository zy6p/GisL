/*!
 * @file mian.cpp
 * @author omega 
 * @date 18/12/2020
 * 
 * @brief test geo
 * @details test geo command line app
 *
 */

#include "geofeature.h"

int main(int argc, char *argv[]) {
    GisL::GeoFeature feature = GisL::GeoFeature("../../data/Practise/practise_6/data/qu.geojson");
    if (!feature.hasError()) {

    } else {
        printf("%s", feature.errorMessage().c_str());
    }

    return 1;
}
