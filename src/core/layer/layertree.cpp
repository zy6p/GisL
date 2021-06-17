/*!
 * @author tau
 * @date 12/30/20
 */

#include "layertree.h"

gisl::LayerTree* gisl::LayerTree::_layerTree = nullptr;

void gisl::LayerTree::append(int fid, gisl::VectorLayer* p) {
    this->layerClassifyMap.insert(std::make_pair(fid, p));
    this->layerMap[fid] = p;
}

void gisl::LayerTree::append(int fid, gisl::RasterBand* p) {
    this->layerClassifyMap.insert(std::make_pair(fid, p));
    this->layerMap[fid] = p;
}

void gisl::LayerTree::append(int fid, gisl::RasterProvider* p) {
    this->providerClassifyMap.insert(std::make_pair(fid, p));
    gisl::LayerTree::providerMap[fid] = p;
}

void gisl::LayerTree::append(int fid, gisl::VectorProvider* p) {
    this->providerClassifyMap.insert(std::make_pair(fid, p));
    gisl::LayerTree::providerMap[fid] = p;
}

gisl::LayerTree* gisl::LayerTree::getLayerTree() {
    if (nullptr == gisl::LayerTree::_layerTree) {
        gisl::LayerTree::_layerTree = new gisl::LayerTree;
    }
    return gisl::LayerTree::_layerTree;
}

gisl::Layer* gisl::LayerTree::getLayer(int fid) {
    return layerMap[fid];
}
gisl::LayerTree::~LayerTree() {}
gisl::DataProvider* gisl::LayerTree::getProvider(int fid) {
    return providerMap[fid];
}
const gisl::LayerMap& gisl::LayerTree::getLayerMap() const noexcept {
    return this->layerMap;
}
const gisl::ProviderMap& gisl::LayerTree::getProviderMap() const noexcept {
    return this->providerMap;
}
const gisl::LayerClassifyMap& gisl::LayerTree::getLayerClassifyMap() const {
    return layerClassifyMap;
}
const gisl::ProviderClassifyMap&
gisl::LayerTree::getProviderClassifyMap() const {
    return providerClassifyMap;
}
