#pragma once

#include "QUADTREE.h"
#include "GeoLayer.h"

void makeIndex(CGeoLayer *layer);

double getDistance(QPointF p1, QPointF p2);