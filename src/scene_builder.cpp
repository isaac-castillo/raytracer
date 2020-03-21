#include "scene_builder.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <memory>

namespace raytracer {

using json = nlohmann::json;

scene_builder::scene_builder(const std::string & filename){

    std::ifstream i("file.json");
    json j;
    i >> j;

    std::unique_ptr<scene> _scene = std::make_unique<scene>();
    
    //size
    _scene->set_width(j["width"]);
    _scene->set_height(j["height"]);


    
}

void create_scene(const std::shared_ptr<scene> scene){


    
    }
}