/*!
 * @author tau
 * @date 12/30/20
 */

#ifndef GISL_LAYERTREE_H
#define GISL_LAYERTREE_H

#include <QAbstractItemModel>
#include <map>
#include <memory>
#include <string>

#include "layer.h"
#include "src/analyse/analyse.h"
#include "src/core/provider/dataprovider.h"

namespace gisl {

using LayerMap = std::map<int, Layer*>;
using ProviderMap = std::map<int, DataProvider*>;

class LayerTree {
public:
    void append(int fid, Layer* p);
    void append(int fid, DataProvider* p);

    static LayerTree* getLayerTree();

    Layer* getLayer(int fid);
    DataProvider* getProvider(int fid);
    ~LayerTree();

protected:
    LayerTree() = default;

    LayerMap layerMap;
    ProviderMap providerMap;

    static LayerTree* _layerTree;
    friend class LayerTreeWidget;
    friend class Analyse;
};
} // namespace gisl

#endif // GISL_LAYERTREE_H
