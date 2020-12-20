#pragma once
class Option
{
public:
	Option();
	~Option();
	int getToolType();
	void setToolType(int type);
protected:
	int type;
};

