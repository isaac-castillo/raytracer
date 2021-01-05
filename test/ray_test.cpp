#include "catch.hpp"

#include "../src/ray.hpp"
#include "../src/util.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace raytracer;

TEST_CASE("Computing a point from a given t", "[ray]") {

    Ray r;
    r.position = vec3(2,3,4);
    r.direction = vec3(1, 0, 0);

    REQUIRE( r.at(0) == vec3(2,3,4));
    REQUIRE( r.at(1) == vec3(3,3,4));
    REQUIRE( r.at(-1) == vec3(1,3,4));
    REQUIRE( r.at(2.5) == vec3(4.5,3,4));

}

TEST_CASE("Translating a ray", "[ray]") {

    Ray r;
    r.position = vec3(1,2,3);
    r.direction = vec3(0, 1, 0);

    auto translation = glm::translate(vec3(3,4,5));
    Ray transformed = util::transform_ray(translation, r); 

    REQUIRE (transformed.position == vec3(4,6,8));
    REQUIRE (transformed.direction == vec3(0,1,0));

}

TEST_CASE("Scaling a ray", "[ray]") {

    Ray r;
    r.position = vec3(1,2,3);
    r.direction = vec3(0, 1, 0);

    auto translation = glm::scale(vec3(2,3,4));
    Ray transformed = util::transform_ray(translation, r); 

    REQUIRE (transformed.position == vec3(2,6,12));
    REQUIRE (transformed.direction == vec3(0,3,0));

}