add_subdirectory(${CMAKE_SOURCE_DIR}/extern/Catch2)

# Abseil
add_subdirectory(abseil-cpp)
target_link_libraries(gisl_static_lib
        absl::strings)

target_link_libraries(tests
        Catch2::Catch2
        gisl_static_lib)

include(CTest)
include(Catch)
catch_discover_tests(tests)
