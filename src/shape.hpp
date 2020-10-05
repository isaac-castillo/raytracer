#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.hpp"
#include "gl_typedef.hpp"
#include <memory>
#include "intersect_result.hpp"

namespace raytracer
{

    enum class shapes
    {
        plane,
        sphere
    };

    class ray;
    class shape
    {

    private:
        material _material;

    protected:
        shape(vec4 normal, mat4 transform) : _transform(transform), _normal(normal){

                                                                    };

        shape()
        {
        }

        shape(vec4 normal) : _normal(normal) {}

        vec4 _normal;
        mat4 _transform = mat4(1.0);

    public:
        virtual void print() = 0;
        virtual intersect_result inside(const ray &ray) = 0;
        mat4 get_transform() const
        {
            return _transform;
        }

        void set_transform(const mat4 transform) {
            _transform = transform;
        }
        virtual vec4 normal(const vec4 &) const = 0;
        material get_material() const
        {
            return _material;
        }

        void set_material(const material &material)
        {
            _material = material;
        }
    };

} // namespace raytracer
#endif