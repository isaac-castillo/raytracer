#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>

#include "scene.hpp"
#include "scene_builder.hpp"
#include "plane.hpp"

using namespace raytracer;


void setup();
void test_camera();
void test_plane();
void test_trace();


camera cam;
scene *s;
tracer *t;

int main()
{

    setup();
    test_camera();
    test_plane();
    test_trace();
    std::cout << "Tests passed" << std::endl;
}

void setup()
{

    scene_builder sb("scenes/test_1.json");

    

    //Mock out a camera
    cam.set_fovy(30);
    cam.set_look_at(vec3(0,0,0));
    cam.set_look_from(vec3(0,0,4));
    cam.set_up(vec3(0,1,0));


    
    // s = sb.create_scene();
}

void test_camera()
{

    auto direction = cam.direction(18, 18, 20, 20);

    assert(abs(direction.x - 0.2169) < 0.1);
    assert(abs(direction.y - -0.2169) < 0.1);
    assert(abs(direction.z - -0.9518) < 0.1);
}

void test_plane()
{

    // intersect_result rd;
    // const vec3 eye = cam.look_from();
    // const vec3 direction = cam.direction(18, 18, 20, 20);
    // for (auto const &p : s->get_shapes()){

    //     rd = p->inside(eye, direction);
    //     assert(rd.shape_ptr == p.get());
    // }



    // assert(rd.intersect == 1);
    // assert(abs(rd.dist - 4.204) < 0.1);
}

void test_trace()
{

    // tracer rt(5, s);

    // auto direction = cam.direction(18, 18, 20, 20);
    // vec4 eye = vec4(cam.look_from(), 1.0f);
}