cmake_minimum_required(VERSION 3.6)
project(rog)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp game_objects.cpp game_objects.h game_manager.h menu.h user_interface.h user_interface.cpp draw_handler.h game_manager.cpp draw_handler.cpp config.h config.cpp)
link_libraries(${CMAKE_SOURCE_DIR}/lib/pdcurses.lib)
add_executable(rog ${SOURCE_FILES} game_objects.cpp game_objects.h)
include_directories(${CMAKE_SOURCE_DIR}/include)
