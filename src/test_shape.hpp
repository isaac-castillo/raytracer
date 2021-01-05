#ifndef TESTSHAPE_CPP
#define TESTSHAPE_CPP

#include "shape.hpp"
#include "gl_typedef.hpp"
#include <vector>

namespace raytracer {
    
    class ray;
    class test_shape : public Shape {

    
    public:
        test_shape(vec3 normal = vec3(0), mat4 transformation = mat4(1.0f));

        std::optional<IntersectResult> inside(const Ray & ray) override;
        void print() override;

        vec3 normal(const vec3 &) const override;


    };

}


#endif