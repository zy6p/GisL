add_library(gis "")

target_sources(gis
        PRIVATE
        ../../src/core/vector.cpp ../../src/core/vectorlayer.cpp ../../src/core/vectorfeature.cpp ../../src/core/spatialreference.cpp ../../src/core/geometry.cpp ../../src/core/geopoint.cpp ../../src/core/geoline.cpp ../../src/core/geopolygon.cpp ../../src/core/geomultipoint.cpp ../../src/core/geomultiline.cpp ../../src/core/geomultipolygon.cpp
        PUBLIC
        ../../src/core/vector.h ../../src/core/vectorlayer.h ../../src/core/vectorfeature.h ../../src/core/spatialreference.h ../../src/core/geometry.h ../../src/core/geopoint.h ../../src/core/geoline.h ../../src/core/geopolygon.h ../../src/core/geomultipoint.h ../../src/core/geomultiline.h ../../src/core/geomultipolygon.h
        )

target_include_directories(gis
        PUBLIC
        ../../src/core
        )
