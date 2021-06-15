//
// Created by km on 6/13/21.
//

#ifndef GISL_LAYERTREEWIDGET_H
#define GISL_LAYERTREEWIDGET_H

#include <QTreeWidget>

#include "core/layer/layertree.h"

namespace gisl {
class LayerTreeWidget : public QTreeWidget {
    Q_OBJECT

public:
    explicit LayerTreeWidget(QWidget* parent);
    ~LayerTreeWidget() override = default;
    void setSelectionModel(QItemSelectionModel* selectionModel) override;
    void updateLayerTree();

protected:
    void dropEvent(QDropEvent* event) override;
    LayerTree* layerTree;
};
} // namespace gisl
#endif // GISL_LAYERTREEWIDGET_H
