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

#include "src/core/vector/vectorlayer.h"

namespace gisl {
using LayerMap = std::map<std::string, VectorLayer*>;

class LayerTree {
public:
  void append(const std::string& s, VectorLayer* p);

  static LayerTree* getLayerTree();
  static std::shared_ptr<LayerTree> getSharedLayerTree();

  VectorLayer* getLayer(const std::string& s);

protected:
  LayerTree() = default;

  LayerMap layerMap;

private:
  static LayerTree* _layerTree;
  static std::shared_ptr<LayerTree> _s_layerTree;
};
} // namespace gisl

#endif // GISL_LAYERTREE_H
