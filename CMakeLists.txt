cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(Magna)

include_directories( ${MY_SOURCE_DIR} )
include_directories("${PROJECT_BINARY_DIR}")

add_executable(magna main.cpp factory.cpp resource.cpp)