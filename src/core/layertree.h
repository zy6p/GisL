/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_LAYERTREE_H
#define GISL_LAYERTREE_H

#include <map>
#include <string>

#include "vectorlayer.h"

namespace GisL {
    typedef std::map<std::string, VectorLayer *> LayerMap;

    class LayerTree {
    public:
        static void append( const std::string &s, VectorLayer *p );

        static LayerTree *getLayerTree( );


    protected:
        LayerTree( ) = default;

        static LayerMap layerMap;

    private:
        static LayerTree *_layerTree;
    };
}

#endif //GISL_LAYERTREE_H
