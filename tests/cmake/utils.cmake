add_library(utils "")

target_sources(utils
        PRIVATE
        ../../src/utils/merror.cpp ../../src/utils/stringoperate.cpp
        PUBLIC
        ../../src/utils/merror.h ../../src/utils/stringoperate.h
        )

target_include_directories(utils
        PUBLIC
        ../../src/utils
        )
