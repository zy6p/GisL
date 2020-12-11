#include "VaoGroup.h"



VaoGroup::VaoGroup()
{
}


VaoGroup::~VaoGroup()
{
}

QOpenGLVertexArrayObject * VaoGroup::getVaoAtLevel(int level)
{
	return vaos.at(level);
}

void VaoGroup::addVao(QOpenGLVertexArrayObject * vao)
{
	vaos.push_back(vao);
}

QOpenGLVertexArrayObject * VaoGroup::removeVao(int level)
{
	QOpenGLVertexArrayObject* vao = vaos.at(level);
	vaos.removeAt(level);
	return vao;
}

QList<QOpenGLVertexArrayObject*> VaoGroup::removeAll()
{
	QList<QOpenGLVertexArrayObject*> copyList = vaos;
	vaos.clear();
	return copyList;
}

int VaoGroup::size()
{
	return vaos.size();
}
