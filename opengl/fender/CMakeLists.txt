cmake_minimum_required(VERSION 2.8)

project(fender)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_subdirectory(fengine)
add_subdirectory(fender_test)

