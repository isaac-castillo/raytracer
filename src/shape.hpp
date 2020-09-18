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

        vec4 _normal;
        mat4 _transform;

    public:
        virtual void print() = 0;
        virtual intersect_result inside(const ray &ray) = 0;
        virtual mat4 get_transform() const = 0;
        virtual vec4 normal() const = 0;
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