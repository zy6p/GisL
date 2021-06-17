/*!
 * @author tau
 * @date 12/30/20
 */

#include "layertree.h"

gisl::LayerTree* gisl::LayerTree::_layerTree = nullptr;

void gisl::LayerTree::append(int fid, gisl::Layer* p) {
  gisl::LayerTree::layerMap[fid] = p;
}

gisl::LayerTree* gisl::LayerTree::getLayerTree() {
  if (nullptr == gisl::LayerTree::_layerTree) {
    gisl::LayerTree::_layerTree = new gisl::LayerTree;
  }
  return gisl::LayerTree::_layerTree;
}

gisl::Layer* gisl::LayerTree::getLayer(int fid) { return layerMap[fid]; }
gisl::LayerTree::~LayerTree() {}
void gisl::LayerTree::append(int fid, gisl::DataProvider* p) {
  gisl::LayerTree::providerMap[fid] = p;
}
gisl::DataProvider* gisl::LayerTree::getProvider(int fid) {
  return providerMap[fid];
}
const gisl::LayerMap& gisl::LayerTree::getLayerMap() const noexcept {
  return this->layerMap;
}
const gisl::ProviderMap& gisl::LayerTree::getProviderMap() const noexcept {
  return this->providerMap;
}
