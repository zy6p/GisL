add_executable(GisTest
        gistest.cpp
        ${GISL_GIS_SUBDIR} ${GISL_UTILS_SUBDIR})
#target_link_libraries(GisTest core)
target_link_libraries(GisTest GDAL)

add_test(
        NAME
        test_gis
        COMMAND
        $<TARGET_FILE:GisTest>)


add_executable(CodecvtTest
        codecvttest.cpp
        ${GISL_CODECVT_SUBDIR})
#target_link_libraries(DaCodecvtTest codecvt)

add_test(
        NAME
        test_codecvt
        COMMAND
        $<TARGET_FILE:CodecvtTest>)