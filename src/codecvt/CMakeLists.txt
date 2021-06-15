set(GISL_CODECVT_SRCS
        dacodecvt.cpp
        dacodecvt.h
        dadecoder.cpp
        dadecoder.h
        daencoder.cpp
        daencoder.h
        daunit.cpp
        daunit.h
        )
add_library(gisl_codecvt_lib ${LIBRARY_TYPE}
        ${GISL_CODECVT_SRCS}
        )
