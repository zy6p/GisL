/*!
 * @author tau 
 * @date 12/30/20
*/

#include "layertree.h"

GisL::LayerTree *GisL::LayerTree::_layerTree = nullptr;

void GisL::LayerTree::append( const std::string &s, GisL::VectorLayer *p ) {
    GisL::LayerTree::layerMap[s] = p;
}

GisL::LayerTree *GisL::LayerTree::getLayerTree( ) {
    if ( nullptr == GisL::LayerTree::_layerTree ) {
        GisL::LayerTree::_layerTree = new GisL::LayerTree;
    }
    return GisL::LayerTree::_layerTree;
}

GisL::VectorLayer *GisL::LayerTree::getLayer( const std::string &s ) {
    return layerMap[s];
}
