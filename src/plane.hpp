#ifndef PLANE_HPP
#define PLANE_HPP

#include "shape.hpp"
#include "gl_typedef.hpp"
#include <vector>

namespace raytracer {
    
    class plane : protected shape {

        public:
            ray_distance inside(const vec3 &initial, const vec3 &direction) override;
            plane(const std::vector<vec4> & vertices);
        
        private:        
            float _dist_to_plane(const vec3 &initial, const vec3 &direction);
            bool _intersect(const vec3 & position_to_plane);
            std::vector<vec4> _vertices;
            vec4 _normal;

    };

}


#endif