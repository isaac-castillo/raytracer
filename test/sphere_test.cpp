#include "catch.hpp"

#include "../src/sphere.hpp"
#include "../src/ray.hpp"
#include "../src/intersect_result.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace raytracer;

TEST_CASE("A Ray intersects a sphere at 2 points ", "[sphere]")
{

    Ray r;
    r.position = vec3(0, 0, -5);
    r.direction = vec3(0, 0, 1);

    Sphere s(1, vec3(0, 0, 0));

    std::optional<IntersectResult> result = s.inside(r);

    REQUIRE(result);
    REQUIRE(result.value().distance == 4);
}

TEST_CASE("A Ray intersects a sphere at one point ", "[sphere]")
{

    Ray r;
    r.position = vec3(0, 1, -5);
    r.direction = vec3(0, 0, 1);

    Sphere s(1, vec3(0, 0, 0));

    std::optional<IntersectResult> result = s.inside(r);

    REQUIRE(result);
    REQUIRE(result.value().distance == 5);
}

TEST_CASE("A Ray doesn't hit the sphere ", "[sphere]")
{

    Ray r;
    r.position = vec3(0, 2, -5);
    r.direction = vec3(0, 0, 1);

    Sphere s(1, vec3(0, 0, 0));

    std::optional<IntersectResult> result = s.inside(r);

    REQUIRE(!result);
}

TEST_CASE("A Ray's origin is  inside the sphere ", "[sphere]")
{

    Ray r;
    r.position = vec3(0, 0, 0);
    r.direction = vec3(0, 0, 1);

    Sphere s(1, vec3(0, 0, 0));

    std::optional<IntersectResult> result = s.inside(r);

    REQUIRE(result);
    REQUIRE(result.value().distance == 1);
}

TEST_CASE("A Ray's origin is 'after' the sphere ", "[sphere]")
{

    Ray r;
    r.position = vec3(0, 0, 5);
    r.direction = vec3(0, 0, 1);

    Sphere s(1, vec3(0, 0, 0));

    std::optional<IntersectResult> result = s.inside(r);

    REQUIRE(!result);
}

TEST_CASE("no transformation on sphere", "[sphere]")
{

    Sphere s;
    REQUIRE(s.get_transform() == mat4(1));
}

TEST_CASE("Translating a sphere", "[sphere]")
{
    auto const translation = glm::translate(vec3(2, 3, 4));
    Sphere s(1.0f, vec3(0, 0, 0), translation);
    REQUIRE(s.get_transform() == translation);
}

TEST_CASE("Intersecting a scaled sphere", "[sphere]")
{
    auto const scale = glm::scale(vec3(2, 2, 2));
    Sphere s(1.0f, vec3(0, 0, 0), scale);

    Ray r;
    r.position = vec3(0, 0, -5);
    r.direction = vec3(0, 0, 1);

    std::optional<IntersectResult> result = s.inside(r);
    REQUIRE(result);
    REQUIRE(result.value().distance == 3);
}

TEST_CASE("Intersecting a translated sphere", "[sphere]")
{

    auto const translate = glm::translate(vec3(5, 0, 0));
    Sphere s(1.0f, vec3(0, 0, 0), translate);

    Ray r;
    r.position = vec3(0, 0, -5);
    r.direction = vec3(0, 0, 1);

    std::optional<IntersectResult> result = s.inside(r);
    REQUIRE(!result);
}

TEST_CASE("Normal of a sphere on x-axis", "[sphere]")
{

    Sphere s;

    auto normal = s.normal(vec3(1, 0, 0));

    INFO("s.normal(..)" << glm::to_string(normal));
    REQUIRE(normal == vec3(1, 0, 0));
}

TEST_CASE("Normal of a sphere on y-axis", "[sphere]")
{

    Sphere s;

    auto normal = s.normal(vec3(0, 1, 0));

    INFO("s.normal(..)" << glm::to_string(normal));
    REQUIRE(normal == vec3(0, 1, 0));
}

TEST_CASE("Normal of a sphere on z-axis", "[sphere]")
{

    Sphere s;

    auto normal = s.normal(vec3(0, 0, 1));
    INFO("s.normal(..)" << glm::to_string(normal));
    REQUIRE(normal == vec3(0, 0, 1));
}

TEST_CASE("Normal of a sphere on somewhere else", "[sphere]")
{

    Sphere s;
    auto root = glm::sqrt(3) / 3;

    auto normal = s.normal(vec3(root, root, root));

    INFO("s.normal(..)" << glm::to_string(normal));
    REQUIRE(glm::all(
        glm::lessThan(
            glm::abs(normal - vec3(root, root, root)),
            vec3(0.01))));
}

TEST_CASE("Normal of a translated sphere", "[sphere]")
{

    auto const translate = glm::translate(vec3(0, 1, 0));

    Sphere s;
    s.set_transform(translate);

    auto normal = s.normal(vec3(0, 1.70711, -0.70711));
    INFO("s.normal(..)" << glm::to_string(normal));

    REQUIRE(glm::all(
        glm::lessThan(
            glm::abs(normal - vec3(0, 0.70711, -0.70711)),
            vec3(0.01))));
}

TEST_CASE("Normal of a transformed sphere", "[sphere]")
{

    auto const scale_rotate = glm::scale(vec3(1, 0.5, 1)) * glm::rotate(glm::degrees(glm::pi<float>() / 5), vec3(0, 0, 1));

    Sphere s;
    s.set_transform(scale_rotate);
    auto normal = s.normal(vec3(0, glm::sqrt(2) / 2, -glm::sqrt(2) / 2));
    INFO("s.normal(..)" << glm::to_string(normal));
    REQUIRE(glm::all(
        glm::lessThan(
            glm::abs(normal - vec3(0, 0.97014, -0.24254)),
            vec3(0.01))));
}
