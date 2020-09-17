#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "gl_typedef.hpp"
#include "scene.hpp"

// Needed for std::shared_ptr
#include <memory>

namespace raytracer
{

    class intersect_result;
    class color;
    class tracer
    {

    private:
        color _trace_reflected(const position &initial, const direction &direction, int counter) const;
        color _compute_lighting(intersect_result &rd, const position &initial, const direction &direction) const;
        intersect_result _closest_shape(const position &initial, const direction &direction) const;

        std::shared_ptr<scene> _scene;
        int _max_depth;

    public:
        tracer(int max_depth, std::shared_ptr<scene> scene);
        color trace(const position &initial, const direction &direction) const;
    };

} // namespace raytracer
#endif