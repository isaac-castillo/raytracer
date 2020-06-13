#include "plane.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>

namespace raytracer {

    plane::plane(const std::vector<vec4> & vertices) : _vertices(vertices), _normal(vec4(glm::triangleNormal(vec3(vertices[0]), vec3(vertices[1]), vec3(vertices[2])), 0.0f)) {

    }

    void plane::print() {

    }
    
    ray_distance plane::inside(const vec3 &initial, const vec3 &direction){


        ray_distance rd;

        
        mat4 reverse = glm::inverse(_transform);
        vec4 reverseInitial = reverse * vec4(initial, 1);
        vec4 d = vec4(direction, 0);
        vec4 reverseDir = reverse * d;



        rd.dist = (_dist_to_plane(vec3(reverseInitial), vec3(reverseDir)));
        if (rd.dist > 0.0001)
        {
            rd.pp = vec3(reverseInitial + reverseDir * rd.dist);
            rd.intersect = _intersect(rd.pp);
            rd.shape_ptr = this;
        }

        return rd;
    }

    bool plane::_intersect(const vec3 & position_to_plane){

        vec3 v0 = vec3(_vertices[1] - _vertices[0]);
        vec3 v1 = vec3(_vertices[2] - _vertices[0]);
        vec3 v2 = position_to_plane - vec3(_vertices[0]);
        float d00 = glm::dot(v0, v0);
        float d01 = glm::dot(v0, v1);
        float d11 = glm::dot(v1, v1);
        float d20 = glm::dot(v2, v0);
        float d21 = glm::dot(v2, v1);
        float d = d00 * d11 - d01 * d01;
        float beta = (d11 * d20 - d01 * d21) / d;
        float gamma = (d00 * d21 - d01 * d20) / d;
        float alpha = 1.0f - beta - gamma;

        return beta >= 0 && gamma >=0 && alpha >= 0; 
    }

    float plane::_dist_to_plane(const vec3 &initial, const vec3 &direction){

        float t = glm::dot(_vertices[0], _normal) - glm::dot(vec4(initial, 0.0f), _normal);
        t = t / glm::dot(vec4(direction, 0.0f), _normal);

        return t;
    }

    mat4 plane::get_transform() const{
        return _transform;
    }

    vec3 plane::normal() const {
        return _normal;
    }
}
