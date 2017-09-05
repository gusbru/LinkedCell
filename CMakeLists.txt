cmake_minimum_required(VERSION 3.8)
project(LinkedCell)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp main.h atom.cpp atom.h linkedcell.cpp linkedcell.h cell.cpp cell.h)
add_executable(LinkedCell ${SOURCE_FILES})