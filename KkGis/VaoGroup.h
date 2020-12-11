#pragma once
#include <qopenglvertexarrayobject.h>
#include <qlist.h>
using namespace std;
class VaoGroup //用于一个feature的整体绘制，将一个feature作为一个整体，以多次绘制的方法构造复杂的图形
{
public:
	VaoGroup();
	~VaoGroup();
	QOpenGLVertexArrayObject* getVaoAtLevel(int level);
	void addVao(QOpenGLVertexArrayObject* vao);
	QOpenGLVertexArrayObject* removeVao(int level);
	QList<QOpenGLVertexArrayObject*> removeAll();
	int size();
private:
	QList<QOpenGLVertexArrayObject*> vaos;
};

