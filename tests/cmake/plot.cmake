add_library(plot "")

target_sources(plot
        PRIVATE
        ../../src/gui/layerrender.cpp ../../src/gui/sld.cpp
        PUBLIC
        ../../src/gui/layerrender.h ../../src/gui/sld.h
        )

target_include_directories(plot
        PUBLIC
        ../../src/gui
        )
