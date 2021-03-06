cmake_minimum_required(VERSION 3.5)
project(videogame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(FREEIMAGE_ROOT "C:\\MinGW\\include\\freeimage")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(FreeImage REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${FREEIMAGE_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp
        Player.cpp Player.h
        Map.cpp Map.h
        Room.cpp Room.h
        RoomWhere.h
        Game.cpp Game.h
        TextureManager.cpp TextureManager.h
        Model.cpp Model.h
        Enemy.h
        Raticate.cpp Raticate.h
        Golem.cpp Golem.h
        Arbok.cpp Arbok.h
        Drawable.cpp Drawable.h
        Bullet.cpp Bullet.h
        Item.cpp Item.h
        TreasureChest.cpp TreasureChest.h
        ParticleEngine.cpp ParticleEngine.h)
add_executable(videogame ${SOURCE_FILES})
target_link_libraries(videogame ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${FREEIMAGE_LIBRARIES})
