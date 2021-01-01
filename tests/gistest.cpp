/*!
 * @file mian.cpp
 * @author omega 
 * @date 18/12/2020
 * 
 * @brief tests geometry
 * @details tests geometry command line app
 *
 */

#include <string>
#include "../src/core/vectorprovider.h"

int main(int argc, char *argv[]) {
    GisL::VectorProvider vector = GisL::VectorProvider( "../resource/practise_6/qu.geojson" );
    if (vector.hasError()) {
        printf("%s", vector.errorMessage().c_str());
    }

//    std::string h = vector.pmVectorLayer[0]->pmCrs->toWKT();
//    printf("%s", h.c_str());

//    for (int i = vector.getLayerCount() - 1; i >= 0; ++i) {
//        vector.pmVectorLayer[i]->fieldCount;
//    }
    return 1;
}
