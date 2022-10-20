cmake_minimum_required(VERSION 3.23)
project(Semester_2)

AUX_SOURCE_DIRECTORY(dir VARIABLE)
set(CMAKE_CXX_STANDARD 14)
include_directories(complex)
add_executable(Semester_2
        complex/complex.h complex/main.cpp)

include_directories("C:/opt/msys/mingw64/include")

