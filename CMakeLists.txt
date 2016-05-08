cmake_minimum_required(VERSION 3.5)
project(videogame)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Player.cpp Player.h
        Map.cpp Map.h
        Room.cpp Room.h
        Game.cpp Game.h)
add_executable(videogame ${SOURCE_FILES})
target_link_libraries(videogame ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
