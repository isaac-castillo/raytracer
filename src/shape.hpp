#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.hpp"
#include "gl_typedef.hpp"

namespace raytracer {

    enum class shapes {
        plane, sphere
    };

    struct ray_distance {

        std::unique_ptr<shape> shape;
        float dist;
        float intersect;

    };

    class shape {

        private:
            material _material;

        protected:
            mat4 _transform; 


        public:
            virtual void print() = 0;
            virtual ray_distance inside(const vec3 & initial, const vec3 & direction);
            virtual mat4 get_transform() const;
            virtual vec3 normal() const;
            material get_material() const{
                return _material;
            }

    };

}
#endif