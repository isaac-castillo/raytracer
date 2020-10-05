#include "scene_builder.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "plane.hpp"
#include <fstream>
#include <iostream>
#include <stack>
#include <memory>
#include <sstream>
#include <glm/gtx/transform.hpp>
namespace raytracer
{

    void rightmultiply(const mat4 &transform, std::stack<mat4> &transfstack)
    {
        mat4 &top = transfstack.top();
        top *= transform;
    }

    template <typename T>
    std::vector<T> readvals(std::stringstream &s, const int numvals)
    {
        std::vector<T> ret_vector;
        for (int i = 0; i < numvals; i++)
        {
            T current;
            s >> current;
            if (s.fail())
            {
                std::cerr << "Failed reading value. ending " << current;
                return ret_vector;
            }
            ret_vector.push_back(current);
        }
        return ret_vector;
    }

    scene_builder::scene_builder(const std::string &filename)
    {
        //input file stream
        std::ifstream ifs;
        ifs.open(filename);

        if (!ifs.is_open())
        {
            std::cerr << "could not open the file" << std::endl;
            exit(-1);
        }

        transformations.push(mat4(1.0));

        std::vector<vec4> _vertices;
        material _material;

        while (ifs.is_open())
        {

            std::string line;
            std::getline(ifs, line);

            if ((line.find_first_not_of(" \t\r\n") != std::string::npos) && (line[0] != '#'))
            {
                std::stringstream sstr(line);
                std::string command;
                sstr >> command;
                if (command == "size")
                {
                    auto vec = readvals<int>(sstr, 2);
                    _scene->set_width(vec[0]);
                    _scene->set_height(vec[1]);
                }
                else if (command == "camera")
                {
                    auto vec = readvals<float>(sstr, 10); // 10 values eye cen up fov

                    vec3 eye{vec[0], vec[1], vec[2]};
                    vec3 center{vec[3], vec[4], vec[5]};
                    vec3 upv{vec[6], vec[7], vec[8]};
                    float fovy{vec[9]};

                    camera cam;
                    cam.set_fovy(fovy).set_look_at(center).set_up(upv).set_look_from(eye);
                    _scene->set_camera(cam);
                }
                else if (command == "attenuation")
                {
                    auto vec = readvals<float>(sstr, 3);
                    _scene->set_attenuation(vec3(vec[0], vec[1], vec[2]));
                }
                else if (command == "translate")
                {
                    auto vec = readvals<float>(sstr, 3);
                    mat4 translate = glm::translate(vec3(vec[0], vec[1], vec[2]));

                    rightmultiply(translate, transformations);
                }
                else if (command == "point")
                {

                    auto vec = readvals<float>(sstr, 6);

                    vec4 lightpos{vec[0], vec[1], vec[2], 1};
                    vec4 lightcolor{vec[3], vec[4], vec[5], 0};

                    light l{light_type::point, lightcolor, lightpos};
                    _scene->add_light(l);
                }
                else if (command == "directional")
                {

                    auto vec = readvals<float>(sstr, 6);

                    vec4 lightpos{vec[0], vec[1], vec[2], 1};
                    vec4 lightcolor{vec[3], vec[4], vec[5], 1};

                    light l{light_type::direction, lightcolor, lightpos};
                    _scene->add_light(l);
                }
                else if (command == "vertex")
                {

                    auto vec = readvals<float>(sstr, 3);
                    _vertices.push_back(vec4(vec[0], vec[1], vec[2], 1.0f));
                }
                else if (command == "tri")
                {

                    auto vec = readvals<float>(sstr, 3);

                    std::vector<vec4> verts;

                    verts.push_back(_vertices[vec[0]]);
                    verts.push_back(_vertices[vec[1]]);
                    verts.push_back(_vertices[vec[2]]);

                    std::unique_ptr<shape> _shape = std::make_unique<plane>(verts);
                    _shape->set_transform(transformations.top());
                    _shape->set_material(_material);
                    _scene->add_shape(_shape);
                }
            }
        }
    }
} // namespace raytracer
