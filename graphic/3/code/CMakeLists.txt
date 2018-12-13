cmake_minimum_required(VERSION 3.9)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)

include_directories(OBJ-Loader/Source)
include_directories(glm)

find_package( OpenCV REQUIRED )
include_directories(opencv)
include_directories(cxxopts/include)

add_executable(render main.cpp render.h Drawer.h transformers.h)
target_link_libraries(render ${OpenCV_LIBS})