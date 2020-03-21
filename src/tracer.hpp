#ifndef RAYTRACER_H
#define RAYTRACER_H

// #include "Transformer.h"
// #include "Shape.h"

#include "gl_typedef.hpp"
#include "scene.hpp"

namespace raytracer {
class tracer
{
    private:

        vec3 _trace_reflected(const vec3 & initial, const vec3 & direction, int counter) const;
        vec3 _compute_lighting(std::unique_ptr<shape> shape, const vec3 &initial, const vec3 &direction) const;
        ray_distance _closest_shape(const vec3 &initial, const vec3 &direction) const;

        scene *_scene;
        int _max_depth;

            // float inPlane(Shape *s, vec3 initial, vec3 direction);
            // bool intersect(vec3 p, Shape *minShape);
            // float inSphere(Shape *s, vec3 initial, vec3 direction);
            // vec3 lighting(Shape *shape, vec3 intersect);
            // bool shadowIntersect(vec3 sInitial, vec3 sDirection, Scene *scene);

        public:
            tracer(int max_depth, scene *scene);
            vec3 trace(const vec3 &initial, const vec3 &direction) const;

            // void BarycentricSolver(vec3 p, vec3 a, vec3 b, vec3 c, float &alpha, float &beta, float &gamma);
        };

} //raytracer
#endif