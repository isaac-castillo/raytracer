#include "test_shape.hpp"

namespace raytracer
{
    test_shape::test_shape(vec3 normal, mat4 transformation) : Shape(normal)
    {
    }

    std::optional<IntersectResult> test_shape::inside(const Ray &ray)
    {
        std::optional<IntersectResult> result;
        return result;
    }
    void test_shape::print()
    {
    }

    vec3 test_shape::normal(const vec3 &) const
    {
        return _normal;
    }
} // namespace raytracer