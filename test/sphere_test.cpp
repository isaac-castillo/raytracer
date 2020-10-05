#include "catch.hpp"

#include "../src/sphere.hpp"
#include "../src/ray.hpp"
#include "../src/intersect_result.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace raytracer;

TEST_CASE("A ray intersects a sphere at 2 points ", "[sphere]") {


    ray r;
    r.position = vec4(0,0,-5, 1);
    r.direction = vec4(0,0,1, 0);


    sphere s(1, vec4(0,0,0,1));

    intersect_result result = s.inside(r);

    REQUIRE( result.intersect );
    REQUIRE (result.distance == 4);

}

TEST_CASE("A ray intersects a sphere at one point ", "[sphere]") {


    ray r;
    r.position = vec4(0,1,-5, 1);
    r.direction = vec4(0,0,1, 0);


    sphere s(1, vec4(0,0,0,1));

    intersect_result result = s.inside(r);

    REQUIRE( result.intersect );
    REQUIRE (result.distance == 5);

}

TEST_CASE("A ray doesn't hit the sphere ", "[sphere]") {


    ray r;
    r.position = vec4(0,2,-5, 1);
    r.direction = vec4(0,0,1, 0);


    sphere s(1, vec4(0,0,0,1));

    intersect_result result = s.inside(r);

    REQUIRE( !result.intersect );

}

TEST_CASE("A ray's origin is  inside the sphere ", "[sphere]") {


    ray r;
    r.position = vec4(0,0,0, 1);
    r.direction = vec4(0,0,1, 0);


    sphere s(1, vec4(0,0,0,1));

    intersect_result result = s.inside(r);

    REQUIRE( result.intersect );
    REQUIRE( result.distance == 1 );

}

TEST_CASE("A ray's origin is 'after' the sphere ", "[sphere]") {


    ray r;
    r.position = vec4(0,0,5, 1);
    r.direction = vec4(0,0,1, 0);

    sphere s(1, vec4(0,0,0,1));

    intersect_result result = s.inside(r);

    REQUIRE( !result.intersect );

}

TEST_CASE("no transformation on sphere", "[sphere]"){

    sphere s;
    REQUIRE ( s.get_transform() == mat4(1) );

}

TEST_CASE("Translating a sphere", "[sphere]"){
    auto const translation = glm::translate(vec3(2,3,4));
    sphere s(1.0f, vec4(0,0,0,1), translation);
    REQUIRE ( s.get_transform() == translation );

}

TEST_CASE("Intersecting a scaled sphere", "[sphere]"){
    auto const scale = glm::scale(vec3(2,2,2));
    sphere s(1.0f, vec4(0,0,0,1), scale);

    ray r;
    r.position = vec4(0,0,-5, 1);
    r.direction = vec4(0,0,1,0);

    intersect_result result = s.inside(r);
    REQUIRE( result.intersect );
    REQUIRE(  result.distance == 3 );

}

TEST_CASE("Intersecting a translated sphere", "[sphere]"){

    auto const translate = glm::translate(vec3(5,0,0));
    sphere s(1.0f, vec4(0,0,0,1), translate);

    ray r;
    r.position = vec4(0,0,-5, 1);
    r.direction = vec4(0,0,1,0);

    intersect_result result = s.inside(r);
    REQUIRE ( !result.intersect );

}

TEST_CASE("Normal of a sphere on x-axis", "[sphere]"){

    sphere s;

    auto normal = s.normal(vec4(1,0,0,1));

    INFO ("s.normal(..)" << glm::to_string(normal) );
    REQUIRE ( normal == vec4(1,0,0,0) );    

}

TEST_CASE("Normal of a sphere on y-axis", "[sphere]"){

    sphere s;

    auto normal = s.normal(vec4(0,1,0,1));

    INFO ("s.normal(..)" << glm::to_string(normal) );
    REQUIRE ( normal == vec4(0,1,0,0));    

}

TEST_CASE("Normal of a sphere on z-axis", "[sphere]"){

    sphere s;

    auto normal = s.normal(vec4(0,0,1,1));
    INFO ("s.normal(..)" << glm::to_string(normal) );
    REQUIRE ( normal == vec4(0,0,1,0));    

}


TEST_CASE("Normal of a sphere on somewhere else", "[sphere]"){

    sphere s;
    auto root = glm::sqrt(3)/3;

    auto normal = s.normal(vec4(root, root, root, 1));

    INFO ("s.normal(..)" << glm::to_string(normal) );
    REQUIRE(    glm::all(
                glm::lessThan(
                glm::abs(   normal - vec4(root, root, root,0)), 
                            vec4(0.01)  )));

}

TEST_CASE("Normal of a translated sphere", "[sphere]"){

    auto const translate = glm::translate(vec3(0,1,0));

    sphere s;
    s.set_transform(translate);

    auto normal = s.normal(vec4(0, 1.70711, -0.70711, 1));
    INFO ("s.normal(..)" << glm::to_string(normal) );

    REQUIRE(    glm::all(
                glm::lessThan(
                glm::abs(   normal - vec4(0, 0.70711, -0.70711,0)),
                            vec4(0.01)  )));

}

TEST_CASE("Normal of a transformed sphere", "[sphere]"){


    auto const scale_rotate = glm::scale(vec3(1,0.5,1)) * glm::rotate(glm::degrees(glm::pi<float>()/5), vec3(0,0,1));

    sphere s;
    s.set_transform(scale_rotate);
    auto normal = s.normal(vec4(0, glm::sqrt(2)/2, -glm::sqrt(2)/2, 1));
    INFO ("s.normal(..)" << glm::to_string(normal) );
    REQUIRE(    glm::all(
                glm::lessThan(
                glm::abs(   normal -  vec4(0, 0.97014, -0.24254, 0)),
                            vec4(0.01)  )));


}
