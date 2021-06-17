set(GISL_ANALYSIS_SRCS
        analysisalg.cpp
        analysisalg.h
        georeference.cpp
        georeference.h
        analysisgui.cpp
        analysisgui.h
        analysis.cpp
        analysis.h)

add_library(gisl_analysis_lib ${LIBRARY_TYPE}
        ${GISL_ANALYSIS_SRCS}
        )

target_include_directories(gisl_analysis_lib PRIVATE
        ${CMAKE_SOURCE_DIR}/src/analysis
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}/src
        ${CMAKE_BINARY_DIR}/src/analysis
        ${CMAKE_BINARY_DIR}/src/ui
        )

target_link_libraries(gisl_analysis_lib
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        ${GDAL_LIBRARY}
        absl::strings
        Eigen3::Eigen
        Qwt::Qwt
        PRIVATE
        gisl_core_lib
        )

target_link_libraries(gisl
        PRIVATE
        gisl_analysis_lib
        )
