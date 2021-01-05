#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "gl_typedef.hpp"

namespace raytracer
{

    class Camera
    {

    private:
        vec3 _look_from{0, 0, 0};
        vec3 _look_at{0, 0, -1};
        vec3 _up{0, 1, 0};
        float _fovy{90.0f};

    public:
        //accessors
        vec3 look_from() const;
        vec3 at() const;
        vec3 up() const;
        float fovy() const;
        vec3 direction(int pixel_x, int pixel_y, int width, int height) const;
        mat4 look_at_matrix() const;

        //manipulators
        Camera &set_look_from(const vec3 &);
        Camera &set_look_at(const vec3 &);
        Camera &set_up(const vec3 &);
        Camera &set_fovy(const float &);
        Camera &set_fovx(const float fovx, int width, int height);
        void print() const;
    };

} // namespace raytracer

#endif