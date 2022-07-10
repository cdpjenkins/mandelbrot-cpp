cmake_minimum_required(VERSION 3.18)
project(mandelbrot)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set (CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(mandelbrot
        main.cpp
        Mandelbrot.cpp
        MandelbrotRenderer.cpp
        SDLContext.cpp
    )

target_link_libraries(mandelbrot ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
