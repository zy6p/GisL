find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cv_h1 feature_extraction.cpp)
target_link_libraries(cv_h1 ${OpenCV_LIBS})

add_executable(cv_h2 pose_estimation_2d2d.cpp)
target_link_libraries(cv_h2 ${OpenCV_LIBS})
