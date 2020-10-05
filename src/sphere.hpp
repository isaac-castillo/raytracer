#ifndef SPHERE_CPP
#define SPHERE_HPP

#include "shape.hpp"
#include "gl_typedef.hpp"
#include <vector>

namespace raytracer {
    
    class ray;
    class sphere : public shape {

    
    public:
        sphere(float radius = 1.0f, vec4 center = vec4(0,0,0,1), mat4 transformation = mat4(1.0f));

        intersect_result inside(const ray & ray) override;
        void print() override;

        vec4 normal(const vec4 &) const override;

    private:

        float _radius;
        vec4 _center;


    };

}


#endif