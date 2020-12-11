#include "GPCUtil.h"

void tesselation(QPolygonF opolygon, gpc_tristrip *tristrip) {
    int vertexNum = opolygon.size();

    //��QVector�еĶ���ת�Ƶ�gpc_vertex������
    gpc_vertex *vertices = new gpc_vertex[vertexNum];
    for (int i = 0; i < vertexNum; i++) {
        vertices[i].x = opolygon[i].x();
        vertices[i].y = opolygon[i].y();
    }

    //����gpc_vertex_list
    gpc_vertex_list vertexList;
    vertexList.num_vertices = vertexNum;//����ĸ���
    vertexList.vertex = vertices;//��������

    //����gpc_polygon
    gpc_polygon polygon;
    polygon.num_contours = 1;//��һ������
    polygon.hole = nullptr;//û�п׶�
    polygon.contour = &vertexList;

    //��ȡ�ֽ���������
    tristrip->num_strips = 0;
    tristrip->strip = nullptr;//�ֽ��������ζ���������������<0,1,2><1,2,3><2,3,4>...

    //�����ʷֶ����
    gpc_polygon_to_tristrip(&polygon, tristrip);
}

bool isConvex(QPolygonF pts) {
    for (int i = 1; i < pts.size() - 1; i++) {
        //�ж�ÿһ����İ�͹��
        QPointF p1 = pts[i - 1];
        QPointF op = pts[i];
        QPointF p2 = pts[i + 1];
        if (multiply(op, p1, p2) > 0) {
            return false;
        }
    }
    return true;
}

//opΪ�м��,p1��һ����,p2�ڶ���
double multiply(QPointF op, QPointF p1, const QPointF p2) {
    double vec[] = {op.x() - p1.x(), op.y() - p1.y()};
    double vec1[] = {p2.x() - op.x(), p2.y() - op.y()};
    double z = vec[0] * vec1[1] - vec[1] * vec1[0];
    return z;
}

CGeoLayer *subvision(CGeoLayer *layer) {
    CGeoLayer *tessalayer = new CGeoLayer();
    for (int i = 0; i < layer->geoObjects.size(); i++) {
        CGeoObject *object = layer->geoObjects[i];
        QPolygonF pts = ((CGeoPolygon *) object)->pts; // �õ���������ж���
        CGeoObject *obj = new CGeoPolygon();
        ((CGeoPolygon *) obj)->setType("Polygon");
        obj->centriod = object->getRect().center();
        gpc_tristrip tristrip;
        tesselation(pts, &tristrip);
        for (int i = 0; i < tristrip.num_strips; i++) {
            for (int j = 0; j < tristrip.strip[i].num_vertices - 2; j++) {
                ((CGeoPolygon *) obj)->addPoint(QPointF(tristrip.strip[i].vertex[j].x, tristrip.strip[i].vertex[j].y));
                ((CGeoPolygon *) obj)->addPoint(
                        QPointF(tristrip.strip[i].vertex[j + 1].x, tristrip.strip[i].vertex[j + 1].y));
                ((CGeoPolygon *) obj)->addPoint(
                        QPointF(tristrip.strip[i].vertex[j + 2].x, tristrip.strip[i].vertex[j + 2].y));
            }
        }
        tessalayer->addObjects(obj);
    }
    return tessalayer;
}