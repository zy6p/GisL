set(TEST_SRC_FILE
        core/testdataprovider.cpp
        )

add_executable(tests
        ${TEST_SRC_FILE})

target_link_libraries(tests
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        ${GDAL_LIBRARY}
        absl::strings
        Eigen3::Eigen
        Qwt::Qwt
        Catch2::Catch2
        PRIVATE
        gisl_core_lib
        gisl_utils_lib
        gisl_codecvt_lib
        gisl_analysis_lib
        )

target_include_directories(tests PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/utils
        ${CMAKE_SOURCE_DIR}/src/codecvt
        ${CMAKE_SOURCE_DIR}/src/analysis
        )

if (WITH_GMT)
    add_executable(gmt_example
            gmt/example1.cpp)

    target_link_libraries(gmt_example
            PUBLIC
            gmt)
endif ()

####################################################
# OpenCV
set(WITH_CV ${DEFAULT_WITH_GMT} CACHE BOOL "Determines is required OpenCV")
mark_as_advanced(WITH_CV)
if (WITH_CV)
    add_subdirectory(cv)
endif ()
