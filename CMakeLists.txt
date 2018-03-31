cmake_minimum_required(VERSION 3.6)
project(rog)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
link_libraries(${CMAKE_SOURCE_DIR}/lib/pdcurses.lib)
add_executable(rog ${SOURCE_FILES})
include_directories(${CMAKE_SOURCE_DIR}/include)
