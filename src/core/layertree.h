/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_LAYERTREE_H
#define GISL_LAYERTREE_H

#include <map>
#include <string>
#include <QAbstractItemModel>

#include "vectorlayer.h"

namespace gisl {
    typedef std::map<std::string, VectorLayer *> LayerMap;

    class LayerTree {
    public:
        void append( const std::string &s, VectorLayer *p );

        static LayerTree *getLayerTree( );

        VectorLayer *getLayer( const std::string &s );


    protected:
        LayerTree( ) = default;

        LayerMap layerMap;

    private:
        static LayerTree *_layerTree;
    };
}

#endif //GISL_LAYERTREE_H
