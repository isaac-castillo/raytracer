#include "scene.hpp"
#include "gl_typedef.hpp"

#include <vector>
#include <iostream>
#include <memory>
#include "shape.hpp"
namespace raytracer {
    

    scene::scene() : _attenuation(vec3(1,0,0)) {

    }
    void scene::set_camera(const vec3 &look_from, const vec3 &look_at, const vec3 &up, const float &fovy){
        _cam.set_look_from(look_from);
        _cam.set_look_at(look_at);
        _cam.set_up(up);
        _cam.set_fovy(fovy);
    }

    void scene::set_camera(const camera &cam){
        _cam = cam;
    }

    void scene::set_height(int height)
    {
        this->_height = height;
    }

    void scene::set_width(int width)
    {
        this->_width = width;
    }

    void scene::print_shapes() const{

        for (auto const & s : _shapes){
            s->print();
        }
    }

    std::vector<vec3> scene::render_scene(const tracer & tracer)
    {

        std::vector<vec3> pixels(_width * _height);
        //return pixels;
        std::cout << "Rendering a scene of size " << _width <<  " x " << _height << "" << std::endl;
        vec4 eye = vec4(_cam.look_from(), 1.0f);

        int i, j;
        for (i = 0; i < _height; i++)
        {

            for (j = 0; j < _width; j++)
            {
                vec4 dirn = vec4(_cam.direction(j, i, _width, _height), 0.0f);
                int counter = 0;

                vec3 res = vec3(255) * tracer.trace(vec3(eye), vec3(dirn));
                pixels[i * _width + j] = res;
                
            }
            
            if (i + j % 100 == 0)
            {
                std::cout << "\b" << float((i + j)) / (_width * _height) * 100 << " \% done " << std::endl;
            }
        }

        return pixels;
    }

    std::vector<light> scene::get_lights(){
        return _lights;
    }

    const std::vector<std::unique_ptr<shape>> & scene::get_shapes(){
        return _shapes;
    }

    void scene::add_shape(std::unique_ptr<shape> & _shape ){

        _shapes.push_back(std::move(_shape));
    }
    void scene::add_light(const light &light){
        _lights.push_back(light);
    }

    int scene::get_width() const {

        return _width;
    }
    int scene::get_height() const {
        return _height;
    }

    vec3 scene::get_attenuation() const {
        return _attenuation;
    }
}