#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>



#include "camera.hpp"
#include "tracer.hpp"
#include "gl_typedef.hpp"
#include "shape.hpp"
#include "light.hpp"

// #include "Transformer.h"
// #include "Shape.h"
// #include "Light.h"
// #include "FreeImage.h"
// #include <string>

namespace raytracer {
class scene
{

private:
    camera _cam;
    std::vector<std::unique_ptr<shape>> _shapes;
    std::vector<light> lights;

    int _width;
    int _height;
    int _num_shapes;



public:
    void set_camera(const vec3 & eye, const vec3 & center, const vec3 & up, const float & fovy);
    void set_camera(const camera & cam);
    void set_height(int height);
    void set_width(int width);
    void print_shapes() const;
    std::vector<std::unique_ptr<shape>> get_shapes();
    std::vector<vec3> render_scene(const tracer & tracer);
    std::vector<light> get_lights();
    // std::string input;
    // std::string type;
    // FIBITMAP *bitmap;
    // std::vector<vec3> image;
    vec3 attenuation;
    // int maxdepth;
    // Scene();
    // void renderScene2();
    // void addShape(Shape *shape);
    // void setWidth(int width);
    // void setHeight(int height);
    // std::vector<vec3> renderScene();
    // int Height();
    // int Width();
    // std::vector<Shape> shapes;
    // vec3 lighting(Shape *shape, vec3 intersect, vec3 posn);
    // std::vector<Light> lights;
    // vec3 ComputeLight(vec3 direction, vec4 lightcolor, vec3 normal, vec3 halfvec, vec4 mydiffuse, vec4 myspecular, float myshininess);
    // void printShapes();
    // void addLight(Light light);
    // std::string filename;
};
}
#endif
