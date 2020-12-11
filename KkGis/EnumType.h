#pragma once

class EnumType {
public:
    enum geometryType {
        POINT, POLYLINE, POLYGON
    };
    enum dataRenderType {
        GEOMETRYTYPE, GRIDTYPE
    };
    enum rendererType {
        SIGNALRGB, STRETCHRGB
    };
    enum resizeDirection {
        LEFT, TOP, RIGHT, BOTTOM, LEFTTOP, RIGHTTOP, RIGHTBOTTOM, LRFTBOTTOM, NOCHANGESIZE
    };
    enum symbolType {
        MARKERSYMBOL, LINESYMBOL, FILLSYMBOL
    };
    enum bufferType {
        VBO, EBO
    };
    enum geoRenderType {
        MARKER_FILL, MARKER_LINE, LINE_LINE, FILL_FILL, FILL_LINE
    };
    enum styleType {
        FILLCOLOR, LINEWIDTH, LINECOLOR, MARKERSIZE, MARKETCOLOR
    };
    enum source {
        GEOJSON, SHAPEFILE, POSTGRESQL, GEOTIFF
    };
    enum operateMode {
        NORMOL, IDENTIFY
    };
    enum selectMode {
        SINGLEMODE, MULTIMODE
    };
    enum dataChangedType {
        NOCHANGEDATA, SPATICALDATA, COLORDATA
    };
    enum indexMode {
        GRIDINDEX, QUADTREE, R
    };//�����������Ĳ���������R+����
    enum quadTree {
        TOPRIGHT, BOTTOMRIGHT, BOTTOMLEFT, TOPLEFT
    };//�Ĳ������ĸ�����
    enum scaleType {
        screenScale, worldScale, normalizeScale
    };
    enum sparitalAnalysisTool {
        KERNEL_DENSITY_ANALYSIS, ACCESSIBILITY_ANALYSIS
    };
};

