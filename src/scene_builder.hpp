#ifndef SCENE_BUIDLER_HPP
#define SCENE_BUILDER_HPP
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include "gl_typedef.hpp"
namespace raytracer
{

    class scene;
    class scene_builder
    {

    public:
        scene_builder(const std::string &filename);
        std::unique_ptr<scene> create_scene();

    private:
        std::unique_ptr<scene> _scene;

        vec3 json2vec(nlohmann::json);
        vec4 json2vec4(nlohmann::json);
        vec3 json2color(nlohmann::json c);
    }; // namespace raytracer
} // namespace raytracer
#endif