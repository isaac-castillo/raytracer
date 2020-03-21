#include <iostream>
#include <string>

#include "scene.hpp"
#include "sceneRW.hpp"

namespace raytracer {
int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cerr << "Missing file! Retry with a scene file." << std::endl;
        return 0;
    }
     
    scene scene;
    sceneRW fr;
    fr.read_file(argv[1], &scene);
    // if (scene.type == "texture")
    //     scene.bitmap = loadImage(scene.input);
    
    
    tracer rt(5, &scene);
    
    std::vector<vec3> pixels = scene.render_scene(rt);

    // std::string s = scene.filename;
    // saveScreenshot(&scene, s, pixels);

    return 1;
}
}