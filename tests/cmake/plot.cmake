add_library(plot "")

target_sources(plot
        PRIVATE
        ../../src/plot/render.cpp ../../src/plot/sld.cpp
        PUBLIC
        ../../src/plot/render.h ../../src/plot/sld.h
        )

target_include_directories(plot
        PUBLIC
        ../../src/plot
        )
