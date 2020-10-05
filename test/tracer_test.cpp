#include "catch.hpp"
#include "../src/tracer.hpp"
#include "test_utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace raytracer;

TEST_CASE("Reflecting a vector at an angle", "[tracer]") {


    ray r;  
    r.direction = vec4(1, -1, 0, 0);

    ray new_ray = util::reflected_ray(r, vec3(0,1,0));

    REQUIRE(new_ray.direction == vec4(1,1,0,0));

}

TEST_CASE("Reflecting a vector directly onto a slanted surface", "[tracer]") {


    ray r;  
    r.direction = vec4(0, -1, 0, 0);

    ray new_ray = util::reflected_ray(r, vec3(glm::sqrt(2)/2,glm::sqrt(2)/2,0));

    REQUIRE(    glm::all(
                glm::lessThan(
                glm::abs(   new_ray.direction -  vec4(1,0,0,0)),
                            vec4(0.01)  )));
}