#pragma once

#include"COption.h"
#include "GeoLayer.h"
#include "Option.h"

class GeoTool {
public:
    GeoTool();

    ~GeoTool();

    void setOption(Option *opt);

    Option *getOption();

    int getToolType();

    virtual int run_tool() = 0;  //�κμ��㶼����һ��ͼ����Ϊ���
protected:
    Option *option;
    int type;

};

