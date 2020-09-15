#ifndef PLANE_HPP
#define PLANE_HPP

#include "shape.hpp"
#include "gl_typedef.hpp"
#include <vector>

namespace raytracer {
    
    
    class plane : public shape {


    public:
        plane(const std::vector<vec4> &vertices);

        ray_distance inside(const position &initial, const direction &direction) override;
        void print() override;
        mat4 get_transform() const override;
        vec3 normal() const override;

    private:
        float _dist_to_plane(const vec3 &initial, const vec3 &direction);
        bool _intersect(const vec3 &position_to_plane);
        std::vector<vec4> _vertices;
        vec4 _normal;

    };

}


#endif