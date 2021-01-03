/*!
 * @author tau 
 * @date 1/1/21
*/

#include "painterfactory.h"
#include "../../core/layertree.h"

void GisL::PainterFactory::getEnvelope( GisL::Rectangle &rectangle ) {
    if ( nullptr == pmEnvelope ) {
        pmEnvelope = &rectangle;
    } else {
        pmEnvelope->merge( rectangle );
    }
}

GisL::Sld *GisL::PainterFactory::getSld( ) const {
    return pmSld;
}

void GisL::PainterFactory::setSld( GisL::Sld *pSld ) {
    PainterFactory::pmSld = pSld;
}

void GisL::PainterFactory::setRandSld( ) {
    pmSld->rand( layerName );

}

void GisL::PainterFactory::getLayerName( const std::string &s ) {
    layerName = s;
}
