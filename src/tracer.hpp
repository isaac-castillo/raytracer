#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "gl_typedef.hpp"
#include "scene.hpp"

// Needed for std::shared_ptr
#include <memory>

namespace raytracer
{

    class intersect_result;
    class ray;
    class tracer
    {

    private:
        vec3 _trace_reflected(const ray &ray, int counter) const;
        vec3 _compute_color(intersect_result &rd, const ray &ray) const;
        intersect_result _closest_shape(const ray &ray) const;

        std::shared_ptr<scene> _scene;
        int _max_depth;

    public:
        tracer(int max_depth, std::shared_ptr<scene> scene);
        vec3 trace(const ray &ray) const;
    };

} // namespace raytracer
#endif