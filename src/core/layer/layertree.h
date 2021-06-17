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

#include "analysis/analysisalg.h"
#include "core/provider/dataprovider.h"
#include "core/provider/rasterprovider.h"
#include "core/provider/vectorprovider.h"
#include "core/raster/rasterband.h"
#include "core/vector/vectorlayer.h"
#include "layer.h"

namespace gisl {

using ProviderClassifyMap = std::
                            map<int, std::variant<DataProvider*, RasterProvider*, VectorProvider*>>;
using LayerClassifyMap =
    std::map<int, std::variant<Layer*, RasterBand*, VectorLayer*>>;
using LayerMap = std::map<int, Layer*>;
using ProviderMap = std::map<int, DataProvider*>;

class LayerTree {
public:
    void append(int fid, VectorLayer* p);
    void append(int fid, RasterBand* p);
    void append(int fid, RasterProvider* p);
    void append(int fid, VectorProvider* p);

    static LayerTree* getLayerTree();
    [[nodiscard]] const LayerMap& getLayerMap() const noexcept;
    [[nodiscard]] const ProviderMap& getProviderMap() const noexcept;

    [[nodiscard]] const LayerClassifyMap& getLayerClassifyMap() const;
    [[nodiscard]] const ProviderClassifyMap& getProviderClassifyMap() const;

    Layer* getLayer(int fid);
    DataProvider* getProvider(int fid);
    ~LayerTree();

private:
    LayerTree() = default;

    LayerClassifyMap layerClassifyMap;
    ProviderClassifyMap providerClassifyMap;
    LayerMap layerMap;
    ProviderMap providerMap;

    static LayerTree* _layerTree;
    friend class LayerTreeWidget;
    friend class AnalysisAlg;
};
} // namespace gisl

#endif // GISL_LAYERTREE_H
