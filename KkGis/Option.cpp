#include "Option.h"


Option::Option()
{
}


Option::~Option()
{
}

int Option::getToolType()
{
	return type;
}

void Option::setToolType(int type)
{
	this->type = type;
}
