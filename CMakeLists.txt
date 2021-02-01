cmake_minimum_required(VERSION 3.17)
project(LMS_One)

# C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(LMS_One main.cpp Library.cpp Library.h Book.cpp Book.h UI.h UI.cpp Novel.cpp Novel.h Play.cpp Play.h)