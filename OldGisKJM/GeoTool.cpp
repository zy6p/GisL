#include "GeoTool.h"

GeoTool::GeoTool() : option(NULL) {
}

GeoTool::~GeoTool() {
}

void GeoTool::setOption(Option *opt) {
    option = opt;
}

Option *GeoTool::getOption() {
    return option;
}

int GeoTool::getToolType() {
    return type;
}
