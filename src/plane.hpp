#ifndef PLANE_HPP
#define PLANE_HPP

#include "shape.hpp"
#include "gl_typedef.hpp"
#include <vector>

namespace raytracer
{

    class Ray;
    class Plane : public Shape
    {

    public:
        explicit Plane(const std::vector<vec3> &vertices);

        // A check to determine whether the vector reaches the plane
        std::optional<IntersectResult> inside(const Ray &ray) override;
        void print() override;
        vec3 normal(const vec3 &v = vec3(1.0f)) const override;

    private:
        float _dist_to_plane(const Ray &ray);
        bool _intersect(const vec3 &position_to_plane);

        std::vector<vec3> _vertices;
    };

} // namespace raytracer

#endif