#pragma once

#include <qopenglvertexarrayobject.h>
#include <qlist.h>

using namespace std;

class VaoGroup //����һ��feature��������ƣ���һ��feature��Ϊһ�����壬�Զ�λ��Ƶķ������츴�ӵ�ͼ��
{
public:
    VaoGroup();

    ~VaoGroup();

    QOpenGLVertexArrayObject *getVaoAtLevel(int level);

    void addVao(QOpenGLVertexArrayObject *vao);

    QOpenGLVertexArrayObject *removeVao(int level);

    QList<QOpenGLVertexArrayObject *> removeAll();

    int size();

private:
    QList<QOpenGLVertexArrayObject *> vaos;
};

