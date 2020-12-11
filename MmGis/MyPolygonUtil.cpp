#include <qpoint.h>
#include <qpolygon.h>
#include "GeoLayer.h"

using namespace std;

bool IsClockwise(QPolygonF pts, double *pArea /* = nullptr */);

double GetCross(QPointF pt1, QPointF pt2, QPointF pt3);

bool IsClockwise(QPolygonF pts, double *pArea /* = nullptr */);

int dcmp(double x);

bool IsOnSegment(QPointF pt1, QPointF pt2, QPointF pt);

bool IsConvexPoint(QPolygonF pts, bool isClockwise, int idx);

bool IsInPolygon(QPolygonF pts, QPointF pt);

// ���� ����Pt1Pt2 �� ����Pt1Pt3 �Ĳ��
double GetCross(QPointF pt1, QPointF pt2, QPointF pt3);

// �ø��ֹ�ʽ�������ε�˳��
bool IsClockwise(QPolygonF pts, double *pArea /* = nullptr */);

void ClipPolygon(QPolygonF pts, bool isClockwise, CGeoLayer *trgleList);
// ���ȣ���������ֵ�ľ���ֵС�� EPS ����Ϊ���

const double EPS = 1E-8;

// ���� ����Pt1Pt2 �� ����Pt1Pt3 �Ĳ��
double GetCross(QPointF pt1, QPointF pt2, QPointF pt3) {
    return (pt2.x() - pt1.x()) * (pt3.y() - pt1.y()) - (pt3.x() - pt1.x()) * (pt2.y() - pt1.y());
}

// �ø��ֹ�ʽ�������ε�˳��
bool IsClockwise(QPolygonF pts, double *pArea /* = nullptr */) {
    double d = 0;
    const size_t size = pts.size();
    for (size_t i = 0; i < size - 1; i++) {
        d += -0.5 * (pts[i + 1].y() + pts[i].y()) * (pts[i + 1].x() - pts[i].x());
    }

    d += -0.5 * (pts[0].y() + pts[size - 1].y()) * (pts[0].x() - pts[size - 1].x());


    // �õ����������Ҫ����
    if (pArea != nullptr) {
        *pArea = fabs(d);
    }

    if (d < 0)
        return true;
    else
        return false;
}

// �Ѷ�����и�������Σ������ص�
// �ݹ�
void ClipPolygon(QPolygonF pts, bool isClockwise, CGeoLayer *trgleList) {
    size_t nSize = pts.size();
    if (3 == nSize) {
        // ֻʣ3����ʱ��ֱ�ӽ�������������б��У������ݹ�
        CGeoObject *obj = new CGeoPolygon();
        ((CGeoPolygon *) obj)->addPoint(pts[0]);
        ((CGeoPolygon *) obj)->addPoint(pts[1]);
        ((CGeoPolygon *) obj)->addPoint(pts[2]);
        trgleList->addObjects(obj);
        return;
    }
    // �ж����һ�����Ƿ���͹��
    // ֮����ѡ���һ���㣬����Ϊ vector �����������һ��Ԫ��Ч�����
    // ������һ���㲻����Ҫ����ѡ�����ڶ����㣬�Դ�����
    for (int i = 1; i < nSize - 1; i++) {
        if (IsConvexPoint(pts, isClockwise, nSize - i)) {
            // �ѵ����ڶ����㡢���һ����͵�һ�������һ����������
            CGeoObject *object = new CGeoPolygon();
            ((CGeoPolygon *) object)->addPoint(pts[nSize - i - 1]);
            ((CGeoPolygon *) object)->addPoint(pts[nSize - i]);
            ((CGeoPolygon *) object)->addPoint(pts[(nSize - i + 1) % nSize]);
            // �ж϶����������Ƿ��������������
            int j = 1;
            for (j = 1; j < nSize - i - 1; j++) {
                if (IsInPolygon(((CGeoPolygon *) object)->pts, pts[j])) {
                    break;
                }
            }
            // ����������������У���������η���Ҫ�󣬽�������������б� trgleList ��
            // �������һ����Ӷ���ε㼯��ɾ��
            // �ݹ飬ֱ���㼯��ֻ��������
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

// �ж϶����ĳ�˵��Ƿ���͹��
bool IsConvexPoint(QPolygonF pts, bool isClockwise, int idx) {
    int nSize = pts.size();

    // ��ȡ�õ�ǰһ����ͺ�һ������±�
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

    // ����õ����������㹹�������Ĳ��
    double cross = GetCross(pts[idx], pts[next_idx], pts[prev_idx]);

    // ����cross�����������εķ����жϸõ��Ƿ�Ϊ͹��
    if ((cross < 0) == isClockwise) {
        return true;
    } else {
        return false;
    }
}

// �ж�һ�����Ƿ��ڶ���Σ���������ָ�����Σ���
// ���߷���ȡָ��y�Ḻ��������ߣ��ж����������ν������
bool IsInPolygon(QPolygonF pts, QPointF pt) {
    int nSize = pts.size();
    int count = 0; //���������ν������

    for (int i = 0; i < nSize; i++) {
        // �����߶��ϣ�����������Ϊ����������
        if (IsOnSegment(pts[i], pts[(i + 1) % nSize], pt)) {
            return true;
        }
            //�������߶��ཻ
        else if ((dcmp(pts[i].x() - pt.x()) > 0 != dcmp(pts[(i + 1) % nSize].x() - pt.x()) > 0) &&
                 dcmp((pts[(i + 1) % nSize].y() - pts[i].y()) / (pts[(i + 1) % nSize].x() - pts[i].x()) *
                      (pt.x() - pts[i].x())
                      + pts[i].y() - pt.y()) > 0) {
            count++;
        }
    }

    // ����Ϊż�� �㲻�ڶ�����ڣ�������
    if (count % 2 == 0) {
        return false;
    } else {
        return true;
    }
}

// �жϵ� Pt �Ƿ����߶� Pt1Pt2 ��
bool IsOnSegment(QPointF pt1, QPointF pt2, QPointF pt) {
    // ��� Pt1Pt x Pt1Pt2 Ϊ0 �� Pt����Pt1Pt2���ӳ�����
    if (0 == dcmp((pt.x() - pt1.x()) * (pt2.y() - pt1.y()) - (pt.y() - pt1.y()) * (pt2.x() - pt1.x())) &&
        min(pt1.x(), pt2.x()) <= pt.x() && pt.x() <= max(pt1.x(), pt2.x()) &&
        min(pt1.y(), pt2.y()) <= pt.y() && pt.y() <= max(pt1.y(), pt2.y())) {
        return true;
    } else {
        return false;
    }
}

// �ж�x��0��С���ھ���֮�ھ���Ϊ���
int dcmp(double x) {
    if (fabs(x) < EPS)
        return 0;
    else
        return x < 0 ? -1 : 1;
}
