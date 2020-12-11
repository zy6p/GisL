#pragma once
class Symbol
{
public:
	Symbol();
	virtual ~Symbol();
	int getType();
protected:
	int type;
};

