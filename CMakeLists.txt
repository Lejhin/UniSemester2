cmake_minimum_required(VERSION 3.23)
project(Semester_2)

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(Semester_2
        ${CMAKE_CURRENT_SOURCE_DIR}/ Aufgaben/Aufgabe2_3/gtest_main.cpp Aufgaben/Aufgabe2_3/IntVector.cpp Aufgaben/Aufgabe2_3/IntVector.h Aufgaben/Aufgabe2_3/test_intvector1.cpp "Aufgaben/Blatt3/3_2/bruch.h" "Aufgaben/Blatt3/3_2/bruchrechnen.cpp")

