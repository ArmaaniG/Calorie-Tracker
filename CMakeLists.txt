cmake_minimum_required(VERSION 3.25)
project(CalorieTracker1)

set(CMAKE_CXX_STANDARD 17)

add_executable(CalorieTracker1 main.cpp)
target_link_libraries(CalorieTracker1 -lOpenGL32 -lfreeGLUT -lglu32)
