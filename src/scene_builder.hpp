#ifndef SCENE_BUIDLER_HPP
#define SCENE_BUILDER_HPP
#include <memory>
#include <string>
#include <stack>
#include <nlohmann/json.hpp>
#include "gl_typedef.hpp"
namespace raytracer
{

    class Scene;
    class scene_builder
    {

    public:
        scene_builder(const std::string &filename);
        std::unique_ptr<Scene> create_scene();

    private:
        std::unique_ptr<Scene> _scene = std::make_unique<Scene>();

        std::stack<mat4> transformations;

    }; // namespace raytracer
} // namespace raytracer
#endif