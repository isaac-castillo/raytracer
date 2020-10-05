#ifndef PLANE_HPP
#define PLANE_HPP

#include "shape.hpp"
#include "gl_typedef.hpp"
#include <vector>

namespace raytracer {
    
    class ray;
    class plane : public shape {

    
    public:
        plane(const std::vector<vec4> &vertices);


        // A check to determine whether the vector reaches the plane
        intersect_result inside(const ray & ray) override;
        void print() override;
        vec4 normal(const vec4 & v=vec4(1.0f)) const override;

    private:
        float _dist_to_plane(const ray & ray);
        bool _intersect(const vec4 &position_to_plane);

        std::vector<vec4> _vertices;

    };

}


#endif