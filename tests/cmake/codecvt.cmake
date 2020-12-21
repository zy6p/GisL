add_library(codecvt "")

target_sources(codecvt
        PRIVATE
        dacodecvt.cpp dadecoder.cpp daencoder.cpp daunit.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/dacodecvt.h ${CMAKE_CURRENT_LIST_DIR}/dadecoder.h ${CMAKE_CURRENT_LIST_DIR}/daencoder.h ${CMAKE_CURRENT_LIST_DIR}/daunit.h
        )

target_include_directories(codecvt
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
