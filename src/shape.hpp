#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.hpp"
#include "gl_typedef.hpp"
#include <memory>
namespace raytracer {

    enum class shapes {
        plane, sphere
    };

    class shape;
    struct ray_distance {

        shape * shape_ptr = nullptr;
        float dist = std::numeric_limits<float>().max();
        float intersect = false;
        vec3 pp = vec3(0, 0, 0);

    };

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
            virtual ray_distance inside(const vec3 & initial, const vec3 & direction) = 0;
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