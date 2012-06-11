include_directories(${PROJECT_SOURCE_DIR}/fengine)
link_directories(${PROJECT_BINARY_DIR}/fengine)

add_executable(fender_test fender_test.cpp)

target_link_libraries(fender_test fengine)
