#include "catch.hpp"

#include "../src/ray.hpp"
#include "../src/util.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace raytracer;

TEST_CASE("Computing a point from a given t", "[ray]") {

    ray r;
    r.position = vec4(2,3,4, 1);
    r.direction = vec4(1, 0, 0, 0);

    REQUIRE( r.at(0) == vec4(2,3,4,1));
    REQUIRE( r.at(1) == vec4(3,3,4,1));
    REQUIRE( r.at(-1) == vec4(1,3,4,1));
    REQUIRE( r.at(2.5) == vec4(4.5,3,4,1));

}

TEST_CASE("Translating a ray", "[ray]") {

    ray r;
    r.position = vec4(1,2,3, 1);
    r.direction = vec4(0, 1, 0, 0);

    auto translation = glm::translate(vec3(3,4,5));
    ray transformed = util::transform_ray(translation, r); 

    REQUIRE (transformed.position == vec4(4,6,8,1));
    REQUIRE (transformed.direction == vec4(0,1,0,0));

}

TEST_CASE("Scaling a ray", "[ray]") {

    ray r;
    r.position = vec4(1,2,3, 1);
    r.direction = vec4(0, 1, 0, 0);

    auto translation = glm::scale(vec3(2,3,4));
    ray transformed = util::transform_ray(translation, r); 

    REQUIRE (transformed.position == vec4(2,6,12,1));
    REQUIRE (transformed.direction == vec4(0,3,0,0));

}