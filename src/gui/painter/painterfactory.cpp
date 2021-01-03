/*!
 * @author tau 
 * @date 1/1/21
*/

#include "painterfactory.h"

void GisL::PainterFactory::getEnvelope( GisL::Rectangle &rectangle ) {
    if ( nullptr == pmEnvelope ) {
        pmEnvelope = &rectangle;
    } else {
        pmEnvelope->merge( rectangle );
    }
}
