#include "geomap.h"

GeoMap::GeoMap() {
}

GeoMap::~GeoMap() {
    for (int i = 0; i < size(); i++) {
        delete layers.at(i);
    }
}

GeoLayer *GeoMap::getLayerAt(int i) {
    return layers.at(i);
}


GeoLayer *GeoMap::getLayerByFullpath(QString fullpath) {
    for (int i = 0; i < size(); i++) {
        GeoLayer *layer = getLayerAt(i);
        if (layer->getFullPath() == fullpath) {
            return layer;
        }
    }
    return NULL;
}

void GeoMap::addLayer(GeoLayer *layer) {
    layers.push_back(layer);
}

GeoLayer *GeoMap::removeLayerAt(int idx) {
    GeoLayer *layer = layers.at(idx);
    layers.removeAt(idx);
    return layer;
}

GeoLayer *GeoMap::remove(GeoLayer *layer) {
    return removeLayerAt(getIdx(layer));
}

QList<GeoLayer *> GeoMap::removeAll() {

    QList < GeoLayer * > copyList = layers;
    layers.clear();
    return layers;
}

int GeoMap::getIdx(GeoLayer *layer) {
    for (int i = 0; i < size(); i++) {
        if (getLayerAt(i) == layer) {
            return i;
        }
    }
    return -1;
}

void GeoMap::removeByFullpath(QString fullpath) {
    removeLayerAt(getIdx(getLayerByFullpath(fullpath)));
}

GeoLayer *GeoMap::getCurrentLayer() {
    return currentLayer;
}

void GeoMap::setCurrentLayer(GeoLayer *layer) {
    this->currentLayer = layer;
}

int GeoMap::size() {
    return layers.size();
}

void GeoMap::moveLayerLevel(int from, int to) {
    if (from >= 0 && from < layers.size() && to >= 0 && to < layers.size()) {
        layers.move(from, to);
    }
}
