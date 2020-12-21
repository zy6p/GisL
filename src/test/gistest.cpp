/*!
 * @file mian.cpp
 * @author omega 
 * @date 18/12/2020
 * 
 * @brief test geometry
 * @details test geometry command line app
 *
 */

#include "src/gis/vector.h"

int main(int argc, char *argv[]) {
    GisL::Vector vector = GisL::Vector("../data/Practise/practise_6/data/qu.geojson");
    if (vector.hasError()) {
        printf("%s", vector.errorMessage().c_str());
    }

    for (int i = vector.getLayerCount() - 1; i >= 0; ++i) {
        vector.pmVectorLayer[i]->featureCount;
    }
    return 1;
}
