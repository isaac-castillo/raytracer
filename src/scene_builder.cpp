#include <nlohmann/json.hpp>
#include <fstream>
#include <memory>
#include <iostream>
#include <string>

#include "scene_builder.hpp"
#include "plane.hpp"
#include "scene.hpp"
namespace raytracer
{

    using json = nlohmann::json;

    scene_builder::scene_builder(const std::string &filename)
    {

        // std::ifstream input_file(filename);
        // json j;
        // input_file >> j;

        // _scene = std::make_unique<scene>();

        // // //size
        // // std::cout << j << std::endl;
        // _scene->set_width(j["size"]["width"]);
        // _scene->set_height(j["size"]["height"]);

        // camera cam;

        // json _cam = j["camera"];
        // cam.set_fovy(_cam["fovy"]);

        // // cam.set_look_at(json2vec(_cam["at"]));
        // // cam.set_look_from(json2vec(_cam["from"]));
        // // cam.set_up(json2vec(_cam["up"]));

        // _scene->set_camera(cam);

        // // std::cout << j << std::endl;
        // for (json j_light : j["lights"])
        // {
        //     // std::cout << j_light << std::endl;

        //     if (j_light["type"] == "directional")
        //     {
        //         light t_light {light_type::direction, json2color(j_light["color"]), json2vec(j_light["position"]) };
        //         _scene->add_light(t_light);
        //     }
        //     else
        //     {
        //         light t_light { light_type::point, json2color(j_light["color"]), json2vec(j_light["position"]) };
        //         _scene->add_light(t_light);
        //     }
        // }

        // // std::cout << j["shapes"] << std::endl;
        // for (json j_plane : j["shapes"]["planes"])
        // {

        //     // std::cout << j_plane << std::endl;
        //     std::vector<vec4> verts;
        //     for (json j_vert : j_plane["vertices"])
        //     {
        //         // std::cout << j_vert << std::endl;
        //         verts.push_back(json2vec(j_vert));
        //     }

        //     material m;
        //     m.ambient = json2vec(j_plane["ambient"]);
        //     m.diffuse = json2vec(j_plane["diffuse"]);

        //     for (json j_triangle : j_plane["triangles"])
        //     {

        //         std::vector<vec4> triangle;
        //         // std::cout << j_triangle << std::endl;
        //         triangle.push_back(verts[j_triangle[0]]);
        //         triangle.push_back(verts[j_triangle[1]]);
        //         triangle.push_back(verts[j_triangle[2]]);
                
        //         std::unique_ptr<shape> p = std::make_unique<plane>(triangle);

        //         p->set_material(m);
        //         _scene->add_shape(p);
        //     }
        // }
    }

    std::unique_ptr<scene> scene_builder::create_scene()
    {

        return std::move(_scene);
    }

    // vec4 scene_builder::json2vec4(json json)
    // {
    //     return vec4(json["x"], json["y"], json["z"], json["w"]);
    // }
    // //helper function
    // vec4 scene_builder::json2vec(json vjson)
    // {
    //     return vec4(vjson["x"], vjson["y"], vjson["z"], 1);
    // }

    // vec4 scene_builder::json2color(json c)
    // {
    //     return vec4(c["red"], c["green"], c["blue"], 1);
    // }
} // namespace raytracer