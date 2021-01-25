cmake_minimum_required(VERSION 3.17)
project(LMS_One)

set(CMAKE_CXX_STANDARD 11)

add_executable(LMS_One main.cpp Library.cpp Library.h LibraryFile.cpp LibraryFile.h UI.h UI.cpp)