set(TEST_SRC_FILE
        core/testdataprovider.cpp
        )

add_executable(tests
        ${TEST_SRC_FILE})

target_link_libraries(tests
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        ${GDAL_LIBRARY}
        gmt
        absl::strings
        Eigen3::Eigen
        Qwt::Qwt
        PRIVATE
        gisl_core_lib
        gisl_utils_lib
        gisl_codecvt_lib
        gisl_analysis_lib
        )

target_include_directories(tests PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/utils
        ${CMAKE_SOURCE_DIR}/src/codecvt
        ${CMAKE_SOURCE_DIR}/src/analysis
        )

add_executable(gmt_example
        gmt/example1.cpp)

target_link_libraries(gmt_example
        PUBLIC
        gmt)

add_subdirectory(cv)