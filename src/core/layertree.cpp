/*!
 * @author tau 
 * @date 12/30/20
*/

#include "layertree.h"

gisl::LayerTree *gisl::LayerTree::_layerTree = nullptr;

void gisl::LayerTree::append( const std::string &s, gisl::VectorLayer *p ) {
    gisl::LayerTree::layerMap[s] = p;
}

gisl::LayerTree *gisl::LayerTree::getLayerTree( ) {
    if ( nullptr == gisl::LayerTree::_layerTree ) {
        gisl::LayerTree::_layerTree = new gisl::LayerTree;
    }
    return gisl::LayerTree::_layerTree;
}

gisl::VectorLayer *gisl::LayerTree::getLayer( const std::string &s ) {
    return layerMap[s];
}
