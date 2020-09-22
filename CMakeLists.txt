cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
project(raytracer)

include_directories(include)
include_directories(include/FreeImage)
include_directories(include/FreeImage/FreeImage)

include_directories(src)
#link_directories(lib)

add_executable(raytracer 

src/camera.cpp
src/main.cpp
src/plane.cpp
src/scene_builder.cpp
src/scene.cpp
src/tracer.cpp
src/shape.hpp
)

add_executable(raytracer_test
src/camera.cpp
src/unit_tests.cpp
src/plane.cpp
src/scene_builder.cpp
src/scene.cpp
src/tracer.cpp
src/shape.hpp
)

target_link_libraries(raytracer -lfreeimage)
