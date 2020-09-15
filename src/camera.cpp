#include "camera.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace raytracer
{

    void camera::set_look_from(const vec3 &look_from)
    {
        this->_look_from = look_from;
    }

    void camera::set_look_at(const vec3 &look_at)
    {
        this->_look_at = look_at;
    }

    void camera::set_up(const vec3 &up)
    {
        this->_up = up;
    }

    void camera::set_fovy(const float &fovy)
    {
        this->fovy = fovy;
    }

    vec3 camera::direction(int i, int j, int w, int h) const
    {

        float alpha = (float)w / h * glm::tan(glm::radians(fovy) / 2) * ((i + 0.5) - w / 2) / (w / 2);
        float beta = glm::tan(glm::radians(fovy) / 2) * (h / 2 - (j + 0.5)) / (h / 2);
        vec3 wvec = glm::normalize(_look_from - _look_at);
        vec3 uvec = glm::normalize(glm::cross(_up, wvec));
        vec3 vvec = glm::cross(wvec, uvec);
        return normalize(alpha * uvec + beta * vvec - wvec);
    }

    vec3 camera::look_from() const
    {
        return _look_from;
    }

    mat4 camera::look_at() const
    {
        return glm::lookAt(_look_from, _look_at, _up);
    }

    void camera::print() const
    {
        std::cout << "camera{";
        std::cout << "look_from=" << glm::to_string(_look_from);
        std::cout << "look_at=" << glm::to_string(_look_at);
        std::cout << "up=" << glm::to_string(_up);
        std::cout << "}" << std::endl;
    }

} // namespace raytracer