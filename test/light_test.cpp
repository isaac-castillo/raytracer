#include "catch.hpp"

#include "../src/light.hpp"
#include "../src/material.hpp"
#include "../src/lighting.hpp"

#include "test_utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace raytracer;

TEST_CASE("calculates light correctly") {

    material m;
    vec4 p(0,0,0,0);

    SECTION("The eye is within the surface and light "){

        vec4 eye(0,0,-1, 1);
        vec4 normal(0,0,-1, 0);

        // light l;
        // l._light_type   = light_type::point;
        // l._color        = vec4(1,1,1, 0);

    }

}
