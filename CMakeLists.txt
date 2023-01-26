cmake_minimum_required(VERSION 3.23)
project(Semester_2)

file(GLOB file_SRC Test2/main.cpp Test2/Uni.cpp)


set(CMAKE_CXX_STANDARD 14)
include_directories(complex)
add_executable(Semester_2
         ${file_SRC})

include_directories("C:/opt/msys/mingw64/include")

