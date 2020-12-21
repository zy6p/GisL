add_library(gis "")

target_sources(gis
        PRIVATE
        ../../src/gis/vector.cpp ../../src/gis/vectorlayer.cpp ../../src/gis/vectorfeature.cpp ../../src/gis/spatialreference.cpp ../../src/gis/geometry.cpp ../../src/gis/geopoint.cpp ../../src/gis/geoline.cpp ../../src/gis/geopolygon.cpp ../../src/gis/geomultipoint.cpp ../../src/gis/geomultiline.cpp ../../src/gis/geomultipolygon.cpp
        PUBLIC
        ../../src/gis/vector.h ../../src/gis/vectorlayer.h ../../src/gis/vectorfeature.h ../../src/gis/spatialreference.h ../../src/gis/geometry.h ../../src/gis/geopoint.h ../../src/gis/geoline.h ../../src/gis/geopolygon.h ../../src/gis/geomultipoint.h ../../src/gis/geomultiline.h ../../src/gis/geomultipolygon.h
        )

target_include_directories(gis
        PUBLIC
        ../../src/gis
        )
