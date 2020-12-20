#include "QuadNode.h"

QuadNode::QuadNode()
{
}

QuadNode::~QuadNode()
{
	for (int i = 0; i < features.size(); i++)
		delete features.at(i);
	for (int i = 0; i < childs.size(); i++)
		delete childs.at(i);
}

QRectF QuadNode::getNodeRect()
{
	return NodeRect;
}

void QuadNode::setNodeRect(QRectF rect)
{
	NodeRect = rect;
}

QList<GeoFeature*> QuadNode::getFeaturesAll()
{
	return features;
}

GeoFeature* QuadNode::getFeatureAt(int i)
{
	return features.at(i);
}

void QuadNode::addFeature(GeoFeature * feature)
{
	features.append(feature);
}

QuadNode * QuadNode::getChildrenAt(int i)
{
	return childs.at(i);
}

void QuadNode::addChild(QuadNode *child)
{
	childs.append(child);
}

void QuadNode::splitRect4(QRectF NodeRect, QRectF Rect[])
{
	double dx, dy;//格网的长和宽

	double startx = NodeRect.left();
	double starty = NodeRect.top();

	dx = abs(NodeRect.width() / 2);
	dy = abs(NodeRect.height() / 2);

	double top, left, bottom, right;

	int k = 0;
	for (int j = 0; j < 2; j++)
	{
		top = starty - dy * j;
		bottom = top - dy;
		for (int i = 0; i < 2; i++)
		{
			left = startx + dx * i;
			right = left + dx;
			//储存每个格子的范围数据
			QRectF quadRect = QRectF(QPointF(left, top), QPointF(right, bottom));
			Rect[k] = quadRect;
			k++;
		}
	}
}