#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "gl_typedef.hpp"
#include "scene.hpp"

namespace raytracer
{

    class ray_distance;
    class color;
    class tracer
    {
    private:
        color _trace_reflected(const position &initial, const direction &direction, int counter) const;
        color _compute_lighting(ray_distance &rd, const position &initial, const direction &direction) const;
        ray_distance _closest_shape(const position &initial, const direction &direction) const;

        scene *_scene;
        int _max_depth;

    public:
        tracer(int max_depth, scene * scene);
        color trace(const position &initial, const direction &direction) const;
    };

} // namespace raytracer
#endif