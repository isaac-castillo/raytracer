cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
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
src/scene.cpp
src/tracer.cpp
src/shape.hpp
src/sphere.cpp
src/scene_builder2.cpp
)

add_executable(raytracer_test
test/main.cpp
test/camera_test.cpp
test/ray_test.cpp
test/sphere_test.cpp
test/tracer_test.cpp
test/light_test.cpp
src/sphere.cpp
src/shape.hpp
src/camera.cpp
)

target_link_libraries(raytracer -lfreeimage)
