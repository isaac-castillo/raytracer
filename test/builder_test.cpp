#include "catch.hpp"
#include "../src/scene_builder.hpp"
#include "../src/scene.hpp"
#include "../src/shape.hpp"
#include "../src/sphere.hpp"
#include "../src/plane.hpp"
#include "../src/material.hpp"
#include "test_utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <memory>
using namespace raytracer;

TEST_CASE("first scene is built: simple square", "[Camera]")
{

    scene_builder sb("scenes/scene1.test");

    std::shared_ptr<Scene> _scene = sb.create_scene();

    CHECK(_scene->get_width() == 640);
    CHECK(_scene->get_height() == 480);

    Camera cam = _scene->get_cam();
    CHECK(cam.look_from() == vec3(-4, -4, 4));
    CHECK(cam.at() == vec3(1, 0, 0));
    CHECK(cam.up() == vec3(0, 1, 0));
    CHECK(cam.fovy() == 30);

    for (auto const &shape : _scene->get_shapes())
    {
        INFO("shape->normal()" << glm::to_string(shape->normal()));
        CHECK(shape->normal() == vec3(0, 0, 1));

        Material _material = shape->get_material();
        CHECK(_material.ambient == vec3(0.1, 0.1, 0.1));
        CHECK(_material.diffuse == vec3(1, 0, 0));
        CHECK(_material.specular == vec3(0, 0, 0));
    }

    auto lights = _scene->get_lights();

    CHECK(lights[0].type == LightType::direction);
    CHECK(lights[0].position == vec3(0, 0, 1));
    CHECK(lights[0].color == vec3(0.5, 0.5, 0.5));

    CHECK(lights[1].type == LightType::point);
    CHECK(lights[1].position == vec3(4, 0, 4));
    CHECK(lights[1].color == vec3(0.5, 0.5, 0.5));
}

TEST_CASE("second scene is built: simple sphere rendered as a red circle", "[Camera]")
{

    scene_builder sb("scenes/scene0.test");

    std::shared_ptr<Scene> _scene = sb.create_scene();

    CHECK(_scene->get_width() == 100);
    CHECK(_scene->get_height() == 100);

    Camera cam = _scene->get_cam();
    CHECK(cam.look_from() == vec3(0, 0, 4));
    CHECK(cam.at() == vec3(0, 0, 0));
    CHECK(cam.up() == vec3(0, 1, 0));
    CHECK(cam.fovy() == 30);

    for (auto const &_shape : _scene->get_shapes())
    {

        auto normal = _shape->normal(vec4(cam.look_from(), 0));
        INFO("shape->normal()" << glm::to_string(normal));
        CHECK(normal == vec3(0, 0, 1));

        Material _material = _shape->get_material();
        CHECK(_material.ambient == vec3(0.1, 0.1, 0.1));
        CHECK(_material.diffuse == vec3(1, 0, 0));
        CHECK(_material.specular == vec3(0, 0, 0));

        /* TODO: Check if a dynamic_cast is really what we want */
        Sphere *_sphere = dynamic_cast<Sphere *>(_shape.get());
        INFO("_sphere->get_center()" << glm::to_string(_sphere->get_center()));

        CHECK(_sphere->get_center() == vec3(0, 0, 0));
    }

    auto lights = _scene->get_lights();

    CHECK(lights[0].type == LightType::direction);
    CHECK(lights[0].position == vec3(0, 0, 1));
    CHECK(lights[0].color == vec3(0.5, 0.5, 0.5));

    CHECK(lights[1].type == LightType::point);
    CHECK(lights[1].position == vec3(4, 0, 4));
    CHECK(lights[1].color == vec3(0.5, 0.5, 0.5));
}