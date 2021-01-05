#include "catch.hpp"
#include "../src/tracer.hpp"
#include "test_utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace raytracer;

TEST_CASE("Reflecting a vector at an angle", "[tracer]") {


    Ray r;  
    r.direction = vec3(1, -1, 0);

    Ray new_ray = util::reflected_ray(r, vec3(0,1,0));

    REQUIRE(new_ray.direction == vec3(1,1,0));

}

TEST_CASE("Reflecting a vector directly onto a slanted surface", "[tracer]") {


    Ray r;  
    r.direction = vec3(0, -1, 0);

    Ray new_ray = util::reflected_ray(r, vec3(glm::sqrt(2)/2,glm::sqrt(2)/2,0));

    REQUIRE(    glm::all(
                glm::lessThan(
                glm::abs(   new_ray.direction -  vec3(1,0,0)),
                            vec3(0.01)  )));
}