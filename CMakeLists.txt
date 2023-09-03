cmake_minimum_required(VERSION 3.18)
project(mandelbrot)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set (CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(mandelbrot
        src/SDLApp.cpp
        src/Complex.cpp
        src/Config.cpp
        src/Mandelbrot.cpp
        src/MandelbrotRenderer.cpp
        src/PngSaver.cpp
        src/RenderedMandelbrot.cpp
        src/SDLContext.cpp)

target_link_libraries(mandelbrot ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
