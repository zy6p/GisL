#pragma once
#include "GeoLayer.h"
#include "gpc.h"

void tesselation(QPolygonF opolygon, gpc_tristrip* tristrip);
bool isConvex(QPolygonF pts);
double multiply(QPointF op, QPointF p1, const QPointF p2);
CGeoLayer* subvision(CGeoLayer *layer);