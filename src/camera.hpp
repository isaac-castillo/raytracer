#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "gl_typedef.hpp"

namespace raytracer
{

    class camera
    {

    private:
        vec3 _look_from;
        vec3 _look_at;
        vec3 _up;
        float fovy;

    public:
        //accessors
        vec3 look_from() const;
        vec3 direction(int i, int j, int w, int h) const;
        mat4 look_at() const;

        //manipulators
        void set_look_from(const vec3 &);
        void set_look_at(const vec3 &);
        void set_up(const vec3 &);
        void set_fovy(const float &);

        void print() const;
    };

} // namespace raytracer

#endif