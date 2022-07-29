cmake_minimum_required(VERSION 3.22)
project(UnigineTest)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)
file(GLOB_RECURSE SOURCES "src/*.*")

add_executable(UnigineTest main.cpp ${SOURCES})
