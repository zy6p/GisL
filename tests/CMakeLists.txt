
set(TEST_SRC_FILE
        core/testdataprovider.cpp
        )

add_executable(tests
        ${TEST_SRC_FILE}
        ${TEST_HDR_FILE})

add_executable(gmt_example
        gmt/example1.cpp)


target_link_libraries(gmt_example
        PUBLIC
        gmt)