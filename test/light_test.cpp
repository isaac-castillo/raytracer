#include "catch.hpp"

#include "../src/light.hpp"
#include "../src/material.hpp"
#include "../src/lighting.hpp"
#include "../src/test_shape.hpp"
#include "test_utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace raytracer;

TEST_CASE("calculates light correctly")
{

    Material m;
    vec4 p(0, 0, 0, 0);

    SECTION("The eye is within the shape and light ")
    {

        glm::vec3 eye(0, 0, -1);
        glm::vec3 normal(0, 0, -1);

        test_shape ts{normal};

        Light l{LightType::point, glm::vec3(1, 1, 1), glm::vec3(0, 0, -10)};

        glm::vec3 dir_to_light = glm::normalize(l.position - eye);
        glm::vec3 color = algorithm::lighting(dir_to_light, &ts, l, normal, normal);

        INFO("color(..)" << glm::to_string(color));
        REQUIRE(color == vec3(1.8, 1.8, 1.8));
    }
}
