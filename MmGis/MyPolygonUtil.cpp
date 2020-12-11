#include <qpoint.h>
#include <qpolygon.h>
#include "GeoLayer.h"

using namespace std;
bool IsClockwise(QPolygonF pts, double* pArea /* = nullptr */);
double GetCross(QPointF pt1, QPointF pt2, QPointF pt3) ;
bool IsClockwise(QPolygonF pts, double* pArea /* = nullptr */);
int dcmp(double x);
bool IsOnSegment(QPointF pt1, QPointF pt2, QPointF pt) ;
bool IsConvexPoint(QPolygonF pts, bool isClockwise, int idx) ;
bool IsInPolygon(QPolygonF pts, QPointF pt) ;
// 返回 向量Pt1Pt2 与 向量Pt1Pt3 的叉积
double GetCross(QPointF pt1, QPointF pt2, QPointF pt3);
// 用格林公式计算多边形的顺逆
bool IsClockwise(QPolygonF pts, double* pArea /* = nullptr */);
void ClipPolygon(QPolygonF pts, bool isClockwise, CGeoLayer* trgleList);
// 精度：两个数差值的绝对值小于 EPS 即认为相等

const double EPS = 1E-8;
// 返回 向量Pt1Pt2 与 向量Pt1Pt3 的叉积
double GetCross(QPointF pt1, QPointF pt2, QPointF pt3) {
	return (pt2.x() - pt1.x())*(pt3.y() - pt1.y()) - (pt3.x() - pt1.x())*(pt2.y() - pt1.y());
}

// 用格林公式计算多边形的顺逆
bool IsClockwise(QPolygonF pts, double* pArea /* = nullptr */)
{
	double d = 0;
	const size_t size = pts.size();
	for (size_t i = 0; i < size - 1; i++) {
		d += -0.5 * (pts[i + 1].y() + pts[i].y()) * (pts[i + 1].x() - pts[i].x());
	}

	d += -0.5 * (pts[0].y() + pts[size - 1].y()) * (pts[0].x() - pts[size - 1].x());


	// 得到面积，视需要而定
	if (pArea != nullptr) {
		*pArea = fabs(d);
	}

	if (d < 0)
		return true;
	else
		return false;
}

// 把多边形切割成三角形，互不重叠
// 递归
void ClipPolygon(QPolygonF pts, bool isClockwise, CGeoLayer* trgleList)
{
	size_t nSize = pts.size();
	if (3 == nSize) {
		// 只剩3个点时，直接将其加入三角形列表中，结束递归
		CGeoObject *obj = new CGeoPolygon();
		((CGeoPolygon*)obj)->addPoint(pts[0]);
		((CGeoPolygon*)obj)->addPoint(pts[1]);
		((CGeoPolygon*)obj)->addPoint(pts[2]);
		trgleList->addObjects(obj);
		return;
	}
	// 判断最后一个点是否是凸点
	// 之所以选最后一个点，是因为 vector 容器操作最后一个元素效率最高
	// 如果最后一个点不符合要求，则选倒数第二个点，以此类推
	for (int i = 1; i < nSize - 1; i++) {
		if (IsConvexPoint(pts, isClockwise, nSize - i)) {
			// 把倒数第二个点、最后一个点和第一个点加入一个三角形中
			CGeoObject *object = new CGeoPolygon();
			((CGeoPolygon*)object)->addPoint(pts[nSize - i - 1]);
			((CGeoPolygon*)object)->addPoint(pts[nSize - i]);
			((CGeoPolygon*)object)->addPoint(pts[(nSize - i + 1) % nSize]);
			// 判断多边形其余点是否在这个三角形中
			int j = 1;
			for (j = 1; j < nSize - i - 1; j++) {
				if (IsInPolygon(((CGeoPolygon*)object)->pts, pts[j])) {
					break;
				}
			}
			// 如果都不在三角形中，则该三角形符合要求，将其加入三角形列表 trgleList 中
			// 并将最后一个点从多边形点集中删除
			// 递归，直至点集中只有三个点
			if (j == nSize - i - 1) {
				trgleList->addObjects(object);
				pts.erase(pts.end() - i);
				ClipPolygon(pts, isClockwise, trgleList);
				break;
			} else {
				continue;
			}
		} else {
			continue;
		}
	}
}

// 判断多边形某端点是否是凸点
bool IsConvexPoint(QPolygonF pts, bool isClockwise, int idx) 
{
	int nSize = pts.size();

	// 获取该点前一个点和后一个点的下标
	int prev_idx = 0, next_idx = 0;
	if (0 == idx) {
		prev_idx = nSize - 1;
		next_idx = 1;
	} else if (nSize - 1 == idx) {
		prev_idx = idx - 1;
		next_idx = 0;
	} else {
		prev_idx = idx - 1;
		next_idx = idx + 1;
	}

	// 计算该点与相邻两点构成向量的叉积
	double cross = GetCross(pts[idx], pts[next_idx], pts[prev_idx]);

	// 根据cross的正负与多边形的方向判断该点是否为凸点
	if ((cross < 0) == isClockwise) {
		return true;
	} else {
		return false;
	}
}

// 判断一个点是否在多边形（本程序中指三角形）内
// 射线法，取指向y轴负半轴的射线，判断射线与多边形交点个数
bool IsInPolygon(QPolygonF pts, QPointF pt) 
{
	int nSize = pts.size();
	int count = 0; //射线与多边形交点个数

	for (int i = 0; i < nSize; i++)	{
		// 点在线段上，本程序中视为在三角形内
		if (IsOnSegment(pts[i], pts[(i + 1) % nSize], pt)) {
			return true;
		}
		//射线与线段相交
		else if ((dcmp(pts[i].x() - pt.x()) > 0 != dcmp(pts[(i + 1) % nSize].x() - pt.x()) > 0) &&
			dcmp((pts[(i + 1) % nSize].y() - pts[i].y()) / (pts[(i + 1) % nSize].x() - pts[i].x()) * (pt.x() - pts[i].x())
			+ pts[i].y() - pt.y()) > 0) {
				count++;
		}
	}

	// 交点为偶数 点不在多边形内，否则在
	if (count % 2 == 0) {
		return false;
	} else {
		return true;
	}
}

// 判断点 Pt 是否在线段 Pt1Pt2 上
bool IsOnSegment(QPointF pt1, QPointF pt2, QPointF pt) 
{
	// 叉积 Pt1Pt x Pt1Pt2 为0 且 Pt不在Pt1Pt2的延长线上
	if (0 == dcmp((pt.x() - pt1.x())*(pt2.y() - pt1.y()) - (pt.y() - pt1.y())*(pt2.x() - pt1.x())) &&
		min(pt1.x(), pt2.x()) <= pt.x() && pt.x() <= max(pt1.x(), pt2.x()) &&
		min(pt1.y(), pt2.y()) <= pt.y() && pt.y() <= max(pt1.y(), pt2.y())) {
			return true;
	} else {
		return false;
	}
}

// 判断x与0大小，在精度之内就认为相等
int dcmp(double x)
{
	if (fabs(x) < EPS)
		return 0;
	else
		return x < 0 ? -1 : 1;
}
