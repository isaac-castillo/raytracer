#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.hpp"
#include "gl_typedef.hpp"
#include <memory>
#include "intersect_result.hpp"

namespace raytracer {

    enum class shapes {
        plane, sphere
    };

    class position;
    class direction;
    
    class shape {

        private:
            material _material;

        protected:

            shape() : _transform(mat4(1.0f)){

            };

            vec3 _normal;
            mat4 _transform; 


        public:
            virtual void print() = 0;
            virtual intersect_result inside(const position &initial, const direction &direction) = 0;
            virtual mat4 get_transform() const = 0;
            virtual vec3 normal() const = 0;
            material get_material() const{
                return _material;
            }

            void set_material(const material & material){
                _material = material;
            }

    };

}
#endif