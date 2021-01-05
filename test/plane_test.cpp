#include "catch.hpp"
#include "../src/plane.hpp"
#include "../src/ray.hpp"
#include "../src/intersect_result.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>

using namespace raytracer;

TEST_CASE("intersecting parallel", "[plane]") {

    auto const scale = glm::scale(vec3(2,2,2));

    std::vector<glm::vec3> vertices;
    vertices.push_back(glm::vec3(-1, 0, 1));
    vertices.push_back(glm::vec3(1, 0, 1));
    vertices.push_back(glm::vec3(1, 0, -1));

    Plane p(vertices);
    Ray r;
    r.position = vec3(0,10,0);
    r.direction = vec3(0,0,1);

    std::optional<IntersectResult> result = p.inside(r);
    REQUIRE( !result );

}

TEST_CASE("intersecting coplanar", "[plane]") {

    auto const scale = glm::scale(vec3(2,2,2));

    std::vector<glm::vec3> vertices;
    vertices.push_back(glm::vec3(-1, 0, 1));
    vertices.push_back(glm::vec3(1, 0, 1));
    vertices.push_back(glm::vec3(1, 0, -1));

    Plane p(vertices);
    Ray r;
    r.position = vec3(0,0,0);
    r.direction = vec3(0,0,1);

    std::optional<IntersectResult> result = p.inside(r);
    // REQUIRE( !result.intersect );
    //TODO
}