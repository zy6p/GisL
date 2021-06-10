////
//// Created by omega on 14/12/2020.
////
//
//#include "layerrender.h"
//
//#include "sld.h"
//
//namespace gisl {
//
//    LayerRender::LayerRender( Geometry &poGeometry, Sld &poSld ) {
//        pmGeometry = &poGeometry;
//        pmSld = &poSld;
//    }
//
//    LayerRender::LayerRender( Geometry &poGeometry ) {
//        pmSld = nullptr;
//        pmGeometry = &poGeometry;
//        init();
//    }
//
//    /*!
//     * @brief init Render with Geometry, not Sld
//     */
//    void LayerRender::init( ) {
//
//    }
//
//    LayerRender &LayerRender::operator=( const LayerRender &rhs ) {
//        return *this;
//    }
//
//
//}