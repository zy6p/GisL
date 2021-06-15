set(GISL_UTILS_SRCS
        log.cpp
        log.h
        ptroperate.cpp
        ptroperate.h
        stringoperate.cpp
        stringoperate.h
        xml.cpp
        xml.h
        )
add_library(gisl_utils_lib ${LIBRARY_TYPE}
        ${GISL_UTILS_SRCS}
        )

target_link_libraries(gisl_utils_lib
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        )
