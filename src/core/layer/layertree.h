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

namespace gisl {

using LayerMap = std::map<int, Layer*>;

class LayerTree {
public:
  void append(int fid, Layer* p);

  static LayerTree* getLayerTree();

  Layer* getLayer(int fid);
  ~LayerTree();

protected:
  LayerTree() = default;

  LayerMap layerMap;

  static LayerTree* _layerTree;
  static std::shared_ptr<LayerTree> _s_layerTree;
};
} // namespace gisl

#endif // GISL_LAYERTREE_H
