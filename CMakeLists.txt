cmake_minimum_required(VERSION 3.18)
project(mandelbrot)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 20)

# Add compiler optimizations for performance testing
if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    add_compile_options(-O3 -ffast-math)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/test)

add_executable(mandelbrot
        src/SDLApp.cpp
        src/Complex.cpp
        src/Config.cpp
        src/Mandelbrot.cpp
        src/MandelbrotRenderer.cpp
        src/PngSaver.cpp
        src/RenderedMandelbrot.cpp
        src/SDLContext.cpp)

add_executable(mandelbrot_unit_test
        src/Mandelbrot.cpp
        src/MandelbrotRenderer.cpp
        src/RenderedMandelbrot.cpp
        test/MandelbrotTest.cpp
        test/MandelbrotRendererTest.cpp
        test/ComplexPerformanceTest.cpp)

target_link_libraries(mandelbrot ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# TODO - ew, this isn't nice. Need to decouple the stuff that we unit-test from the the SDL stuff
target_link_libraries(mandelbrot_unit_test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
